#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <Windows.h>
#include <stdbool.h>

#include "../SLL/singlyLinkedList.h"

#define ADMIN_USERNAME 		"admin"
#define ADMIN_PASSWORD 		1111
#define VISITOR_USERNAME 	"visitor"
#define VISITOR_PASSWORD	2222
#define INITIAL_MIN_OPTION  0
#define INITIAL_MAX_OPTION	20
#define MAX_ID_LEN 10
#define MAX_AGE_LEN 3



typedef enum userTypes
{
	US_NO_USER,
	US_ADMIN,
	US_VISITOR

}US_user_status_t;

typedef enum optionTypes
{
	OP_NO_OPTION,
	OP_ADD_NEW_EMPLOYEE,
	OP_MODIFY_EXISTING_EMPLOYEE,
	OP_DELETE_EXISTING_EMPLOYEE,
	OP_DELETE_ALL_EMPLOYEES,
	OP_VIEW_EXISTING_EMPLOYEE,
	OP_VIEW_ALL_EXISTING_EMPLOYEES,
	OP_LOG_OUT,
	OP_EXIT_SYSTEM
}EN_choosedOption_t;


typedef enum requestStatus
{
	RE_FULFILLED,
	RE_NOT_FULLFIL
}EN_requestStatus_t;


// define a function  to create an initial list of employees
SinglyLinkedList_t *UI_initial_list_screen(void);

// login screen to validate username and password
US_user_status_t UI_login_screen(void);

// define a function to display the main menu and get the user input
EN_choosedOption_t UI_main_menu_screen(US_user_status_t *currentUser);

// define a function to add a new employee to the list
void UI_add_employee_screen(SinglyLinkedList_t *employeesList);

// define a function to delete an employee from the list
void UI_delete_employee_screen(SinglyLinkedList_t *employeesList);

// delete all employees data 
void UI_delete_all_employees_screen(SinglyLinkedList_t *employessList);

// define a function to modify an employee data in the list
void UI_modify_employee_screen(SinglyLinkedList_t *employeesList);

// define a function to view an employee data in the list
void UI_view_employee_screen(SinglyLinkedList_t *employeesList);

// define a function to view all employees in the list
void UI_view_all_employees_screen(SinglyLinkedList_t *employeesList);

// define a function to exit the program with different options
EN_choosedOption_t UI_exit_screen(SinglyLinkedList_t *employessList);

// define a function to exit the program with different options
bool UI_log_out_screen(void);


#endif

