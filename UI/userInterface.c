#include "userInterface.h"
#include <windows.h>
// define a function to  create an initial list of employees
SinglyLinkedList_t *UI_initial_list_screen(void)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================                 INITIAL LIST                ===========================\n");
    printf("\n===================================================================================================\n");
    SinglyLinkedList_t *newListPtr;
    int userInput = 0;
    char inputStr[10];
    do
    {
        printf("ENTER NUMBER BETWEEN   %d   AND   %d\n", INITIAL_MIN_OPTION, INITIAL_MAX_OPTION);
        printf("FOR INITIAL NUMBER OF EMPLOYEES IN THE LIST : ");
        fflush(stdin);
        fgets(inputStr, 10, stdin);             // read the user input as a string
        userInput = strtol(inputStr, NULL, 10); // convert the string to an integer
        if (userInput > 0 && userInput <= 20)
        {
            newListPtr = SLL_create_initial_list(userInput);
            printf("A LIST OF %d EMPLOYEES IS CREATED\n", userInput);
        }
        else if (userInput == 0)
        {
            newListPtr = SLL_create_initial_list(userInput);
            printf("EMPTY EMPLOYEES LIST IS CREATED");
        }
        else
        {
            printf("%d IS NOT A VALID OPTION; PLEASE TRY AGAIN\n", userInput);
            userInput = -1; // set userInput to an invalid value to repeat the loop
        }

    } while (userInput < INITIAL_MIN_OPTION || userInput > INITIAL_MAX_OPTION); // repeat the loop until userInput is valid
    Sleep(2000);
    return newListPtr;
}

// login screen to validate username and password
US_user_status_t UI_login_screen(void)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================                   LOG IN                    ===========================\n");
    printf("\n===================================================================================================\n");
    char userNameInput[10] = {0};
    int passwordInput = 0;
    US_user_status_t loginValidation = US_NO_USER;
    printf("USER NAME : ");
    fflush(stdin);
    fgets(userNameInput, sizeof(userNameInput), stdin);
    // Remove the newline character from the user name input
    userNameInput[strcspn(userNameInput, "\n")] = '\0';
    printf("USER PASSWORD : ");
    // Read the user password input as a string and convert it to an integer
    char passwordStr[10] = {0};
    fflush(stdin);
    fgets(passwordStr, sizeof(passwordStr), stdin);
    passwordInput = strtol(passwordStr, NULL, 10);
    // Compare the user name and password with the predefined constants
    if (passwordInput == ADMIN_PASSWORD && stricmp(userNameInput, ADMIN_USERNAME) == 0)
    {
        printf("ADMIN LOG IN SUCCEEDED\n");
        loginValidation = US_ADMIN;
    }
    else if (passwordInput == VISITOR_PASSWORD && stricmp(userNameInput, VISITOR_USERNAME) == 0)
    {
        printf("VISITOR LOG IN SUCCEEDED\n");
        loginValidation = US_VISITOR;
    }
    else
    {
        printf("LOG IN FAILED DUE TO INVALID USERNAME OR PASSWORD \nTRY AGAIN\n");
    }
    Sleep(2000);
    return loginValidation;
}

// define a function to display the main menu and get the user input
EN_choosedOption_t UI_main_menu_screen(US_user_status_t *currentUser)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================                  MAIN MENU                  ===========================\n");
    printf("\n===================================================================================================\n");
    EN_choosedOption_t inputOption = OP_NO_OPTION;
    char inputBuffer[10]; // a char array to store the input
    char changeUserInputOption;
    // show available options and read user inpoit
    printf("CHOOSE ONE OF THE FOLLOWING\n");
    printf("%d : ADD A NEW EMPLOYEE\n", OP_ADD_NEW_EMPLOYEE);
    printf("%d : MODIFY DATA OF AN EXISTING EMPLOYEE\n", OP_MODIFY_EXISTING_EMPLOYEE);
    printf("%d : DELETE DATA OF AN EXISTING EMPLOYEE\n", OP_DELETE_EXISTING_EMPLOYEE);
    printf("%d : DELETE DATA OF ALL EXISTING EMPLOYEES\n", OP_DELETE_ALL_EMPLOYEES);
    printf("%d : VIEW DATA OF AN EXISTING EMPLOYEE\n", OP_VIEW_EXISTING_EMPLOYEE);
    printf("%d : VIEW DATA OF ALL EXISTING EMPLOYEES\n", OP_VIEW_ALL_EXISTING_EMPLOYEES);
    printf("%d : LOG OUT AND BACK TO LOG IN SCREEN\n", OP_LOG_OUT);
    printf("%d : DESTROY LIST AND TERMINATE PROGRAM\n", OP_EXIT_SYSTEM);
    while (inputOption == OP_NO_OPTION)
    {
        printf("\n=================");
        printf("\nENTER YOU CHOICE : ");
        strcpy(inputBuffer, "");
        changeUserInputOption = '\0';
        fflush(stdin);
        fgets(inputBuffer, sizeof(inputBuffer), stdin); // read the input as a string
        inputBuffer[strcspn(inputBuffer, "\n")] = 0;    // remove the newline character
        inputOption = strtol(inputBuffer, NULL, 10);    // convert the input to an int
        if (inputOption < OP_ADD_NEW_EMPLOYEE || inputOption > OP_EXIT_SYSTEM)
        {
            /// invalid input continue
            printf("INVALID OPTION ; CHOOSE ONE OF THE AVAILABLE OPTIONS\nTRY AGAIN\n");
            inputOption = OP_NO_OPTION;
            Sleep(2000);
            continue;
        }
        else if (inputOption <= OP_DELETE_ALL_EMPLOYEES && *currentUser == US_VISITOR)
        {
            //  valid input and valid user
            printf("INVALID OPTION ; YOU ARE LOGGED IN AS VISITOR\n");
            printf("YOU CANNOT ADD, DELTE OR MODIFY DATA\n");
            printf("YOU CAN LOGOUT AND LOGIN AGAIN WITH ADMIN USER NAME \n");
            printf("TO GO TO LOGOUT SCREEN PRESS 'Y' OR ANY OTHER TO CONTINUE AS VISITOR ");
            fflush(stdin);
            changeUserInputOption = '\0';
            changeUserInputOption = getc(stdin);
            if (changeUserInputOption == 'Y' || changeUserInputOption == 'y')
            {
                //*currentUser = US_NO_USER;
                inputOption = OP_LOG_OUT;
                printf("\n\nYOU WILL BE REDIRECTED TO LOG OUT SCREEN\n");
                Sleep(2000);
                break;
            }
            else
            {
                inputOption = OP_NO_OPTION;
            }
        }
    }
    Sleep(2000);
    return inputOption;
}

// define a function to add a new employee to the list
void UI_add_employee_screen(SinglyLinkedList_t *employeesList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================                 ADD EMPLOYEE                ===========================\n");
    printf("\n===================================================================================================\n");
    employee_t *newEmplData;
    char nameBuffer[MAX_NAME_LEN] = {0};
    char titleBuffer[MAX_TITLE_LEN] = {0};
    char idBuffer[MAX_ID_LEN] = {0};
    float salaryBuffer = 0;
    char ageBuffer[MAX_AGE_LEN] = {0};
    char nextOptionUserInput = '\0';
    SLL_status_t addNewEmplStatus;
    while (1)
    {
        newEmplData = NULL;
        strcpy(nameBuffer, "");
        strcpy(titleBuffer, "");
        strcpy(idBuffer, "");
        strcpy(ageBuffer, "");
        nextOptionUserInput = '\0';
        addNewEmplStatus = SLL_OK;
        newEmplData = (employee_t *)malloc(sizeof(employee_t)); // allocate memory for the new employee data
        if (newEmplData == NULL)                                // check for null pointer
        {
            printf("Memory allocation failed.\n");
            Sleep(2000);
            return;
        }

        printf("PLEASE ENTER EMPLOYEE DATA\n");
        // read the employee name from the user input
        printf("\nEMPLOYEE NAME     :");
        fflush(stdin);
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = '\0';
        strcpy(newEmplData->name, nameBuffer);
        // read the employee id from the user input
        printf("\nEMPLOYEE ID       :");
        fflush(stdin);
        fgets(idBuffer, sizeof(idBuffer), stdin);
        idBuffer[strcspn(idBuffer, "\n")] = '\0';
        newEmplData->id = strtol(idBuffer, NULL, 10);
        // read the employee title from the user input
        printf("\nEMPLOYEE TITLE    :");
        fflush(stdin);
        fgets(titleBuffer, sizeof(titleBuffer), stdin);
        titleBuffer[strcspn(titleBuffer, "\n")] = '\0';
        strcpy(newEmplData->title, titleBuffer);
        // read the employee age from the user input
        printf("\nEMPLOYEE AGE      :");
        fflush(stdin);
        fgets(ageBuffer, sizeof(ageBuffer), stdin);
        ageBuffer[strcspn(ageBuffer, "\n")] = '\0';
        newEmplData->age = strtol(ageBuffer, NULL, 10);
        // read the employee salary from the user input
        printf("\nEMPLOYEE SALARY   :");
        fflush(stdin);
        scanf("%f", &salaryBuffer);
        newEmplData->salary = salaryBuffer;

        // append the new employee data to the list
        addNewEmplStatus = SLL_append_node(employeesList, newEmplData);
        if (addNewEmplStatus == SLL_OK)
        {
            printf("NEW EMPLOYEE ADDED SUCCESSFULLY\n");
        }
        else // handle the case when the append operation fails
        {
            printf("ERROR: Could not add the new employee to the list.\n");
            free(newEmplData); // free the memory allocated for the new employee data
        }

        printf("\nPRESS 'Y' TO ADD A NEW EMPLOYEE OR ANY OTHER KEY TO GO BACK TO MAIN MENU : ");
        nextOptionUserInput = '\0';
        fflush(stdin);
        nextOptionUserInput = getc(stdin);
        if (nextOptionUserInput == 'Y' || nextOptionUserInput == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    printf("\n\nYOU WILL BE REDIRECTED TO MAIN MENU \n");
    Sleep(2000);
    return;
}

// define a function to delete an employee from the list
void UI_delete_employee_screen(SinglyLinkedList_t *employeesList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================               DELETE EMPLOYEE               ===========================\n");
    printf("\n===================================================================================================\n");
    char nameBuffer[MAX_NAME_LEN];
    node_t *nodeBuffer;
    SLL_status_t findByNameState;
    SLL_status_t deleteStatus;
    char nextOptionUserInput = {0};
    while (1)
    {
        strcpy(nameBuffer, "");
        nodeBuffer = NULL;
        findByNameState = SLL_OK;
        deleteStatus = SLL_OK;
        nextOptionUserInput = '\0';
        printf("ENTER THE NAME OF THE EMPLOYEE YOU WANT TO DELETE : ");
        fflush(stdin);
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = '\0';
        // find the node by name in the list
        findByNameState = SLL_find_by_name(employeesList, nameBuffer, &nodeBuffer);
        if (findByNameState == SLL_NODE_NOT_FOUND)
        {
            printf("EMPLOYEE NOT FOUND\n");
            Sleep(2000);
        }
        else
        {
            printf("\nARE YOU SURE YOU WANT TO DELETE : \n");
            SLL_print_employee(nodeBuffer->employeeData);
            printf("\nPRESS 'Y' TO CONFIRM DELETE OR ANY OTHER KEY TO GO BACK TO KEEP AND CONTINUE : ");

            fflush(stdin);
            nextOptionUserInput = getc(stdin);
            if (nextOptionUserInput == 'Y' || nextOptionUserInput == 'y')
            {
                // delete the node by id from the list
                deleteStatus = SLL_delete_node_by_id(employeesList, nodeBuffer->employeeData.id);
                if (deleteStatus == SLL_OK && findByNameState != SLL_NODE_NOT_FOUND)
                {
                    printf("\nEMPLOYEE DELETE SUCCESS\n");
                }
                else // handle the case when the delete operation fails
                {
                    printf("\nERROR: Could not delete the employee.\n");
                }
            }
            else
            {
                printf("\nDelete denied.  Employee still exist\n");
            }
        }

        printf("\nPRESS 'Y' TO DELETE ANOTHER EMPLOYEE OR ANY OTHER KEY TO GO BACK TO MAIN MENU : ");

        fflush(stdin);
        nextOptionUserInput = getc(stdin);
        if (nextOptionUserInput == 'Y' || nextOptionUserInput == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }

    Sleep(2000);
    return;
}

// delete all employees data
void UI_delete_all_employees_screen(SinglyLinkedList_t *employessList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================            DELETING ALL EMPLOYEES           ===========================\n");
    printf("\n===================================================================================================\n");
    printf("PROCEEDING WITH THIS OPTION DELETING ALL DATA REDIRECT YOU BACK TO MAIN MENU\n");
    printf("ARE YOU SURE YOU WANT TO PROCEED\n");
    printf("ENTER 'Y' TO PROCEED OR ANY OTHER TO CANCEL AND BACK TO MAIN MENU : ");

    char userInput;

    fflush(stdin);
    userInput = getc(stdin);
    if (userInput == 'y' || userInput == 'Y')
    {
        // delete the entire list
        SLL_free_nodes_keep_list(employessList);
        printf("ALL EMPLOYEES DATA DELETED\n");
        printf("YOU WILL BE REDIRECTED TO MAIN MENU\n");
    }
    else
    {
        printf("DELETING ALL EMPLOYEES DATA IS CANCELED\n\n");
        printf("YOU WILL BE REDIRECTED TO MAIN MENU\n\n");
    }

    Sleep(2000);
    return;
}

// define a function to modify an employee data in the list
void UI_modify_employee_screen(SinglyLinkedList_t *employeesList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================               MODIFY EMPLOYEE               ===========================\n");
    printf("\n===================================================================================================\n");
    char nameBuffer[MAX_NAME_LEN];
    SLL_status_t findByNameState;
    node_t *requestedNode; // pointer to the node to be modified
    employee_t *newEmplData;
    char userInput;
    SLL_status_t modifyStatus;
    char nextOptionUserInput;
    while (1)

    {
        strcpy(nameBuffer, "");
        findByNameState = SLL_OK;
        requestedNode = NULL;
        newEmplData = NULL;
        userInput = '\n';
        modifyStatus = SLL_OK;
        nextOptionUserInput = '\n';

        printf("ENTER THE NAME OF THE EMPLOYEE YOU WANT TO MODIFY : ");
        fflush(stdin);
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = '\0';
        // find the node by name in the list
        findByNameState = SLL_find_by_name(employeesList, nameBuffer, &requestedNode);
        if (findByNameState == SLL_NODE_NOT_FOUND)
        {
            printf("EMPLOYEE NOT FOUND\n");
            Sleep(2000);
        }
        else
        {
            SLL_print_employee(requestedNode->employeeData);
            newEmplData = (employee_t *)malloc(sizeof(employee_t));
            if (newEmplData == NULL)
            {
                printf("Memory allocation failed for temp empl data in modify screen.\n");
                Sleep(2000);
                continue;
                ;
            }
            *newEmplData = requestedNode->employeeData; // copy the existing employee data to the new data
            printf("EMPLOYEE NAME : %s", newEmplData->name);
            printf("\nPRESS 'Y' TO MODIFY OR ANY OTHER KEY TO CONTINUE : ");

            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                printf("ENTER NEW NAME : ");
                fflush(stdin);
                fgets(newEmplData->name, sizeof(newEmplData->name), stdin);
                newEmplData->name[strcspn(newEmplData->name, "\n")] = '\0';
            }
            printf("EMPLOYEE TITLE : %s", newEmplData->title);
            printf("\nPRESS 'Y' TO MODIFY OR ANY OTHER KEY TO CONTINUE : ");
            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                printf("ENTER NEW TITLE : ");
                fflush(stdin);
                fgets(newEmplData->title, sizeof(newEmplData->title), stdin);
                newEmplData->title[strcspn(newEmplData->title, "\n")] = '\0';
            }

            printf("EMPLOYEE ID : %d", newEmplData->id);
            printf("\nPRESS 'Y' TO MODIFY OR ANY OTHER KEY TO CONTINUE : ");
            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                printf("ENTER NEW ID : ");
                fflush(stdin);
                scanf("%d", &newEmplData->id);
            }
            printf("EMPLOYEE AGE : %d", newEmplData->age);
            printf("\nPRESS 'Y' TO MODIFY OR ANY OTHER KEY TO CONTINUE : ");
            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                printf("ENTER NEW AGE : ");
                fflush(stdin);
                scanf("%d", &newEmplData->age);
            }

            printf("EMPLOYEE SALARY : %.2f", newEmplData->salary);
            printf("\nPRESS 'Y' TO MODIFY OR ANY OTHER KEY TO CONTINUE : ");
            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                printf("ENTER NEW SALARY : ");
                fflush(stdin);
                scanf("%f", &newEmplData->salary); // use %f instead of %d for float
            }

            printf("THE DATA TO BE SAVED IS : \n"); // use \n instead of /n
            SLL_print_employee(*newEmplData);

            printf("PRESS 'Y' TO SAVE OR ANY OTHER TO CANCEL : ");
            fflush(stdin);
            userInput = getc(stdin);
            if (userInput == 'Y' || userInput == 'y')
            {
                // modify the employee data by id in the list
                modifyStatus = SLL_modify_emplyee_by_id(employeesList, requestedNode->employeeData.id, *newEmplData);
                if (modifyStatus == SLL_MODIFICATION_IS_DONE)
                {
                    printf("EMPLOYEE DATA MODIFIED SUCCESSFULLY\n");
                }
                else
                {
                    printf("ERROR: Could not modify the employee data.\n");
                }
            }
            else
            {
                printf("MODIFICATION CANCELED : CHANGES DISCARDED\n");
            }
        }
        printf("\nPRESS 'Y' TO MODIFY ANOTHER EMPLOYEE OR ANY OTHER KEY TO GO BACK TO MAIN MENU : ");

        fflush(stdin);
        nextOptionUserInput = getc(stdin);
        if (nextOptionUserInput == 'Y' || nextOptionUserInput == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    free(newEmplData); // free the memory allocated for the new employee data
}

// define a function to view an employee data in the list
void UI_view_employee_screen(SinglyLinkedList_t *employeesList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================                VIEW EMPLOYEE                ===========================\n");
    printf("\n===================================================================================================\n");
    char nameBuffer[MAX_NAME_LEN];
    SLL_status_t findByNameState;
    node_t *requestedNode; // pointer to the node to be viewed
    char nextOptionUserInput;
    if (employeesList->size == 0)
    {
        printf("***********************************************\n");
        printf("<<<<  YOU ARE TRYING TO VIEW AN EMPTY LIST >>>>\n");
        printf("***********************************************\n");
        printf("\n\nYOU WILL BE REDIRECTED TO MAIN MENU\n");
        Sleep(2000);
        return;
    }
    while (1)
    {

        printf("ENTER THE NAME OF THE EMPLOYEE YOU WANT TO VIEW : ");
        fflush(stdin);
        fgets(nameBuffer, sizeof(nameBuffer), stdin);
        nameBuffer[strcspn(nameBuffer, "\n")] = '\0';
        // find the node by name in the list
        findByNameState = SLL_find_by_name(employeesList, nameBuffer, &requestedNode);
        if (findByNameState == SLL_NODE_NOT_FOUND)
        {
            printf("EMPLOYEE NOT FOUND\n");
            Sleep(2000);
        }
        else
        {
            // print the employee data using the pointer
            SLL_print_employee(requestedNode->employeeData);
        }
        printf("\nPRESS 'Y' TO VIEW ANOTHER EMPLOYEE OR ANY OTHER KEY TO GO BACK TO MAIN MENU : ");

        fflush(stdin);
        nextOptionUserInput = getc(stdin);
        if (nextOptionUserInput == 'Y' || nextOptionUserInput == 'y')
        {
            continue;
        }
        else
        {
            break;
        }
    }
    printf("\n\nYOU WILL BE REDIRECTED TO MAIN MENU\n");
    Sleep(2000);
    return;
}

// define a function to view all employees in the list
void UI_view_all_employees_screen(SinglyLinkedList_t *employeesList)
{
    system("cls");
    printf("\n===================================================================================================\n");
    printf("\n===========================              VIEW ALL EMPLOYES              ===========================\n");
    printf("\n===================================================================================================\n");
    if (employeesList->size == 0)
    {
        printf("***********************************************\n");
        printf("<<<<  YOU ARE TRYING TO VIEW AN EMPTY LIST >>>>\n");
        printf("***********************************************\n");
        printf("\n\nYOU WILL BE REDIRECTED TO MAIN MENU\n");
        
    }
    else
    {
        // print the list using the SLL_print_list function
        SLL_print_list(employeesList);

        printf("PRESS ANY KEY TO GO BACK TO MAIN MENU");
        getc(stdin);
    }

    Sleep(2000);
    return;
}

// define a function to exit the program with different options
EN_choosedOption_t UI_exit_screen(SinglyLinkedList_t *employessList)
{
    system("cls");
    EN_choosedOption_t option = OP_EXIT_SYSTEM;
    printf("\n===================================================================================================\n");
    printf("\n===========================                 EXIT SYSTEM                ===========================\n");
    printf("\n===================================================================================================\n");
    printf("PROCEEDING WITH THIS OPTION DELETING ALL DATA AND TERMINATES THE PROGRAM\n");
    printf("ARE YOU SURE YOU WANT TO PROCEED\n");
    printf("ENTER 'Y' TO PROCEED OR ANY OTHER TO CANCEL AND BACK TO MAIN MENU : ");

    char userInput;

    fflush(stdin);
    userInput = getc(stdin);

    if (userInput == 'y' || userInput == 'Y')
    {
        // delete the entire list
        SLL_free_list(employessList);
        printf("LIST DESTROYED\n");
        printf("EXITING SYSTEM\n");
    }
    else
    {
        printf("EXITING CANCELED\n\n");
        printf("YOU WILL BE REDIRECTED TO MAIN MENU\n\n");
        option = OP_NO_OPTION;
    }
    Sleep(2000);
    return option;
}

// define a function to exit the program with different options
bool UI_log_out_screen(void)
{
    system("cls");
    bool option = false;
    printf("\n===================================================================================================\n");
    printf("\n===========================                 LOGGING OUT                 ===========================\n");
    printf("\n===================================================================================================\n");
    printf("PROCEEDING WITH THIS OPTION KEEPS ALL DATA, REDIRECT YOU TO LOGIN SCREEN\n");
    printf("ARE YOU SURE YOU WANT TO PROCEED\n");
    printf("ENTER 'Y' TO PROCEED OR ANY OTHER TO CANCEL AND BACK TO MAIN MENU : ");

    char userInput;

    fflush(stdin);
    userInput = getc(stdin);

    if (userInput == 'y' || userInput == 'Y')
    {
        option = true;
        printf("YOU WILL BE REDIRECTED TO LOG IN SCREEN\n");
    }
    else
    {
        printf("LOGGING OUT CANCELED\n\n");
        printf("YOU WILL BE REDIRECTED TO MAIN MENU\n\n");
        option = false;
    }
    Sleep(2000);
    return option;
}
