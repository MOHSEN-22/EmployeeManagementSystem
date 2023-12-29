***************************************************************************************
***************************************************************************************


gcc -o a.exe app.c EMS\employeeManagementSystem.c UI\userInterface.c SLL\singlyLinkedList.c


***************************************************************************************
***************************************************************************************
                                  EMPLOYEE MANAGEMENT SYSTEM
***************************************************************************************
***************************************************************************************
starting point  ->  app.c
***************************************************************************************
***************************************************************************************
1 : TOP : 	-variables and flow control statements to mange UI components from MIDDLE LAYERS
		- has nothing to do with what is shown	
*****************************
	 EMPLOYEE MANAGEMENT SYSTEM
*****************************
		EMS.H #include(singlyLinkedList.h ,userInterface.h )
		EMS.c
			employeeManagementSystem
				login
				intilize LIST
				show options , proceed to user choice
					add employee
					modify employee
					delete employee
					delete all employees
					view employee
					view all employees
					log out
					exit system
				go back to login
			terminate the program

***************************************************************************************
2 : MIDDLE	:	-consists of UI components each component is a dependent UI_exit_screen
			-screen donot call each other, redirection is manged by APPLICATION layer
			-use features of liked list offered by LOWER layer
*****************************
  USER INTERFACE COMPONENTS
*****************************
		userInterface.h
			#includes(Window.h,stdbool.h,singlyLinkedList.h)
			#define(ADMIN_USERNAME, ADMIN_PASSWORD, VISITOR_USERNAME, VISITOR_PASSWORD
			, INITIAL_MIN_OPTION, INITIAL_MAX_OPTION, MAX_ID_LEN,MAX_AGE_LEN)
			typedef(EN_choosedOption_t,US_user_status_t,EN_requestStatus_t)
			declarations of functions defined in userInterface.c
		userInterface.c
			UI_initial_list_screen,	UI_log_out_screen
			UI_main_menu_screen, UI_add_employee_screen
			UI_delete_employee_screen, UI_delete_all_employees_screen
			UI_modify_employee_screenUI_view_employee_screen
			UI_view_all_employees_screen, UI_exit_screen,UI_log_out_screen
***************************************************************************************

3 : LOWER :	-customized linked list functions for emploees MANAGEMENT
			-it doesnt depend by any form on the upper layers
*****************************
	LINKED LIST
*****************************
		singlyLinkedList.h
			#includes(stdio.h,stdlib.h,string.h)
			#define(MAX_NAME_LEN,  MAX_TITLE_LEN, MAX_NODES)
			typedef(employee_t,node_t,SinglyLinkedList_t,SLL_status_t)
			declarations of functions defined in singlyLinkedList.c
		singlyLinkedList.c
			SLL_create_empty_list, SLL_create_initial_list
			SLL_create_node, SLL_append_node
			SLL_find_by_name, SLL_print_employee
			SLL_print_list, SLL_delete_node_by_id
			SLL_free_list, SLL_modify_emplyee_by_id
			SLL_free_nodes_keep_list, SLL_print_sequence_employee
	

***************************************************************************************
***************************************************************************************









_______________________________________________________________________________________
***************************************************************************************
*************************            LOG IN SCREEN            *************************
***************************************************************************************
user name		password		authoroties
admin 			1111			every thing
visitor 		2222			viewing data and exiting BUT NOT (add , delete , modify)

-you have to input valid user name and its related password to continue to program
-usernames are INSENSITIVE
-if you tried (add , delete , modify) while logged in as visitor you will have the options
	to go back to main menu or logout and try login as admin
-at any point you can choose logout from main menu and after logging out you will be
	redirected to login file

***************************************************************************************
*************************         INITIAL LIST SCREEN         *************************
***************************************************************************************
-you will see this screen ONCE in the program lifetime
-you can choose number between 0 and 20 for initial numbers of employees in the list
-choose 0 to start with an empty list
-you cannot retrieve data after delection or after initiation

***************************************************************************************
*************************           MAIN MENU SCREEN          *************************
***************************************************************************************
-this screen purpose is to chose an operation to perform like add, delete, view ....
-available options are 1-add 2-modify 3-delete single 4-delete all 5-view single 
	6-view all 7-logout 8-exit
-for add, delete, modify, view single screens you will be asked if you want to 
	repeate the operation before going back to main menu
-if you choosed invalid operation as delete while you are logged in as visitor
	you will have the option to choose another operation or go to logout screen
-from this screen you can go to two screens only 1-choosed operation screen
	2-logout screen in case you want to change login data.

***************************************************************************************
*************************         ADD EMPLOYEE SCREEN         *************************
***************************************************************************************
-you will be asked to enter employee data one by one
-then show data before save
-you can discard or save data
-you will be asked if you want to add another employee before goto main menu

***************************************************************************************
*************************       MODIFY EMPLOYEE SCREEN        *************************
***************************************************************************************
-you will be asked to enter the name of the employee
-if not found you will get a message
-if found the data will be shown data 
-for each of employee parameters you will be asked if you want to keep or change
	if you choosed to keep you will move to next parameter
	if you choosed to modify you will be asked for new value
-after that new data is shown and you have the option to confirm or cancel modify
-you will be asked if you want to modify another employee

***************************************************************************************
*************************       DELETE EMPLOYEE SCREEN        *************************
***************************************************************************************
-you will be asked to enter the name of the employee
-if not found you will get a message
-if found the data will be shown and you have the option to confirn or cancel delete
-you will be asked if you want to modify another employee

***************************************************************************************
*************************     DELETE ALL EMPLOYEE SCREEN      *************************
***************************************************************************************
-you will be asked for confirmation to delete all data.
	if you confirm data is deleted and you are redirected to main menu
	if you cancel it you are redirected to main menu

***************************************************************************************
*************************        VIEW EMPLOYEE SCREEN         *************************
***************************************************************************************
-you will be asked for the name if not found you get a message if found data is shown
-you will be asked if you want to show another one
-you will be redirected to main menu

***************************************************************************************
*************************      VIEW ALL EMPLOYEES SCREEN      *************************
***************************************************************************************
-this screen shows data of all employees and pressing any key takes you back to 
	main menu

***************************************************************************************
*************************           LOG OUT SCREEN            *************************
***************************************************************************************
-you will be asked for confirmation if you confirm logout ypu are logged out and 
	redirected to login screen this is irreversible . if you denied log out you 
	will be redirected to main menu

***************************************************************************************
*************************             EXIT SCREEN             *************************
***************************************************************************************
-you will be notified that yoy are about to delete all data and destroy list 
	and terminate the program 
-if confirmed all data is deleted , list is distroyed and program terminates
-if denied you will be redirected to main menu


