#include "employeeManagementSystem.h"
int employeeManagementSystem(void) 
{
    US_user_status_t currentUserStatus = US_NO_USER;
    EN_choosedOption_t currentOption = OP_NO_OPTION;
    SinglyLinkedList_t *employeesList;
    bool changeUser = true;
    bool listCreated = false;
    while (1) // main loop
    {
        while (changeUser == true) // login loop
        {
            currentUserStatus = UI_login_screen();
            if (currentUserStatus != US_NO_USER)
            {
                changeUser = false;
            }
        }
        if (listCreated == false) // create list once
        {
            employeesList = UI_initial_list_screen();
            listCreated = true;
        }
        while (currentOption == OP_NO_OPTION) // main menu loop
        {
            currentOption = UI_main_menu_screen(&currentUserStatus);
        }
        if (currentUserStatus == US_NO_USER) // check if user logged out
        {
            changeUser = true;
            continue; // go back to login loop
        }
        char name_of_current_option[40] = {0};
        while (currentOption != OP_NO_OPTION) // option loop
        {
            switch (currentOption) // handle different options
            {
            case OP_ADD_NEW_EMPLOYEE:
                UI_add_employee_screen(employeesList);
                break;
            case OP_MODIFY_EXISTING_EMPLOYEE:
                UI_modify_employee_screen(employeesList);
                break;
            case OP_DELETE_EXISTING_EMPLOYEE:
                UI_delete_employee_screen(employeesList);
                break;
            case OP_DELETE_ALL_EMPLOYEES:
                UI_delete_all_employees_screen(employeesList);
                break;
            case OP_VIEW_EXISTING_EMPLOYEE:
                UI_view_employee_screen(employeesList);
                break;
            case OP_VIEW_ALL_EXISTING_EMPLOYEES:
                UI_view_all_employees_screen(employeesList);
                break;
            case OP_LOG_OUT:
                changeUser = UI_log_out_screen();
                currentOption = OP_NO_OPTION;
                break;
            case OP_EXIT_SYSTEM:
                currentOption = UI_exit_screen(employeesList);
                break;

            default:
                break;
            }
            if (currentOption == OP_EXIT_SYSTEM) // check if user exited
            {
                return 0; // end the program
            }
            else if (currentOption == OP_LOG_OUT) // check if user logged out
            {
                changeUser = true;
                break; // exit the option loop
            }
            else // reset the option
            {
                currentOption = OP_NO_OPTION;
            }
        }
    }
}