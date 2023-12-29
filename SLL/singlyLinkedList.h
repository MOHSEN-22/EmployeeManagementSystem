#ifndef SINGLY_LINKED_LIST_H
#define SINGLY_LINKED_LIST_H

// Include the required header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 30
#define MAX_TITLE_LEN 30
#define MAX_NODES 100


// Define a structure to store employee data
typedef struct tag_empl
{
	char name[MAX_NAME_LEN];
	int age;
	float salary;
	char title[MAX_TITLE_LEN];
	int id; 
}employee_t;

// Define a structure to store a node of the singly linked list
typedef struct tag_node 
{
	employee_t employeeData; // The data of the node
	struct tag_node* next; // The pointer to the next node
}node_t;

// Define a structure to store the singly linked list
typedef struct SLL_tag
{
	node_t *head; // The pointer to the head node
	int size; // The size of the list
}SinglyLinkedList_t;

// Define an enumeration to store the status codes of the operations
typedef enum
{
	SLL_OK, // The operation was successful
	SLL_NULL_POINTER, // One or more of the pointers were NULL
	SLL_NODE_NOT_FOUND, // The node was not found in the list
	SLL_NODE_FOUND, // The node was found in the list
	SLL_MODIFICATION_IS_DONE, // The node data was modified
	SLL_DELETEED_SUCCESSFULLY, // The node was deleted from the list
	SLL_LIST_FULL,//List is at max size defined in .h MAX_NODES
	SLL_LIST_EMPTY //List is empty
}SLL_status_t;

// Declare the functions to perform operations on the singly linked list

// Create a new empty singly linked list and return a pointer to it
SinglyLinkedList_t *SLL_create_empty_list(void);

// Create a new singly linked list with some initial data and return a pointer to it
SinglyLinkedList_t *SLL_create_initial_list(int listSize);

// Create a new node with the given data and return a pointer to it
node_t *SLL_create_node(employee_t *data);

// Append a new node with the given data to the end of the list and return a status code
SLL_status_t SLL_append_node(SinglyLinkedList_t *list, employee_t *data);

// Find a node by the employee name and return a pointer to it
SLL_status_t SLL_find_by_name(SinglyLinkedList_t *list, char *name, node_t **pointerToEmployeeNode);

// Print the data of an employee in a formatted way
void SLL_print_employee(employee_t data);

// Print the entire list by calling the print employee function for each node
void SLL_print_list(SinglyLinkedList_t *list);

// Delete a node by the given id and return a status code
SLL_status_t SLL_delete_node_by_id(SinglyLinkedList_t *list, int id);

// Free the entire list and return a status code
SLL_status_t SLL_free_list(SinglyLinkedList_t *list);

// Modify the employee data of a node by the given id and return a status code
SLL_status_t SLL_modify_emplyee_by_id(SinglyLinkedList_t *list, int id, employee_t newData);

// Free the nodes of the list but keep the list structure and return a status code
SLL_status_t SLL_free_nodes_keep_list(SinglyLinkedList_t *list);

// used as the repetitive part of the view list function
void SLL_print_sequence_employee(employee_t data);

#endif