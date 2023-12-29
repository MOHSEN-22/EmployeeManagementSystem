

#include "singlyLinkedList.h"
// Create a new empty singly linked list and return a pointer to it
SinglyLinkedList_t *SLL_create_empty_list(void)
{
	// Allocate memory for a new list structure
	SinglyLinkedList_t *newList = (SinglyLinkedList_t *)malloc(1 * sizeof(SinglyLinkedList_t));
	// Check if memory allocation was successful
	if (newList == NULL)
	{
		printf("SLL_create_empty_list: Memory allocation failed for newList\n");
		free(newList);
		return NULL;
	}
	// Initialize the size and head of the list
	newList->size = 0;
	newList->head = NULL;
	return newList;
}

// Create a new singly linked list with some initial data and return a pointer to it
SinglyLinkedList_t *SLL_create_initial_list(int listSize)
{
	// Allocate memory for a new list structure
	SinglyLinkedList_t *newList = (SinglyLinkedList_t *)malloc(1 * sizeof(SinglyLinkedList_t));
	// Check if memory allocation was successful
	if (newList == NULL)
	{
		printf("SLL_create_initial_list: Memory allocation failed for newList\n");
		return NULL;
	}
	// Initialize the size and head of the list
	newList->size = 0;
	newList->head = NULL;
	// Create an array of sample employee data
	employee_t sample_employees[20] = {
		{"Ahmed Ali", 25, 1234.56, "Engineer", 2589},
		{"Fatima Hassan", 32, 2345.67, "Manager", 4158},
		{"Mohamed Omar", 28, 3456.78, "Accountant", 7215},
		{"Sara Ahmed", 30, 4567.89, "Teacher", 3365},
		{"Khaled Ibrahim", 35, 5678.90, "Doctor", 1982},
		{"Noura Mohamed", 27, 6789.01, "Nurse", 6554},
		{"Yasser Ahmed", 33, 7890.12, "Lawyer", 7269},
		{"Hala Ali", 29, 8901.23, "Journalist", 2446},
		{"Omar Ali", 31, 9012.34, "Architect", 3721},
		{"Rania Hassan", 26, 123.45, "Designer", 5896},
		{"Ahmed Mohamed", 34, 234.56, "Developer", 4172},
		{"Nadia Ahmed", 28, 345.67, "Writer", 6283},
		{"Ibrahim Khaled", 37, 456.78, "Chef", 1938},
		{"Mona Noura", 29, 567.89, "Artist", 6547},
		{"Amr Yasser", 32, 678.90, "Photographer", 7294},
		{"Reem Hala", 27, 789.01, "Singer", 2468},
		{"Ali Omar", 30, 890.12, "Actor", 3749},
		{"Hassan Rania", 25, 901.23, "Dancer", 5968},
		{"Mohamed Ahmed", 33, 12.34, "Teacher", 4193},
		{"Ahmed Nadia", 31, 23.45, "Lawyer", 6328}};
	// Loop through the array and append each employee to the list
	for (int i = 0; i < listSize; i++)
	{
		SLL_append_node(newList, &sample_employees[i]);
	}
	return newList;
}

// Create a new node with the given data and return a pointer to it
node_t *SLL_create_node(employee_t *data)
{
	// Allocate memory for a new node structure
	node_t *newNode = (node_t *)malloc(1 * sizeof(node_t));
	// Check if memory allocation was successful
	if (newNode == NULL)
	{
		printf("SLL_create_node: Memory allocation failed for newNode\n");
		return NULL;
	}
	// Copy the data to the node
	newNode->employeeData = *data;
	// Set the next pointer of the node to NULL
	newNode->next = NULL;
	return newNode;
}

// Append a new node with the given data to the end of the list and return a status code
SLL_status_t SLL_append_node(SinglyLinkedList_t *list, employee_t *data)
{
	// Check if the list or data pointers are NULL
	if (list == NULL || data == NULL)
	{
		printf("SLL_append_node: parameters passed contain NULLpointer\n");
		return SLL_NULL_POINTER;
	}
	// Create a new node with the data
	node_t *newNode = SLL_create_node(data);
	// Check if the node creation was successful
	if (newNode == NULL)
	{
		printf("SLL_append_node: Memory allocation failed for newNode SLL_create_node returned NULL\n");
		return SLL_NULL_POINTER;
	}
	if (list->size >= MAX_NODES)
	{
		printf("SLL_append_node: failed due to list at  MAX SIZE = %d\n", MAX_NODES);
		return SLL_LIST_FULL;
	}
	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Check if the list is empty
	if (list->head == NULL)
	{
		// Set the head of the list to the new node
		list->head = newNode;
	}
	else
	{
		// Loop until the end of the list
		while (current->next != NULL)
		{
			// Move the pointer to the next node
			current = current->next;
		}
		// Set the next pointer of the last node to the new node
		current->next = newNode;
	}
	// Increment the size of the list
	list->size++;
	return SLL_OK;
}

// Find a node by the employee name and return a pointer to it
SLL_status_t SLL_find_by_name(SinglyLinkedList_t *list, char *name, node_t **pointerToEmployeeNode)
{
	// Check if any of the pointers are NULL
	if (list == NULL || name == NULL || pointerToEmployeeNode == NULL)
	{
		printf("SLL_find_by_name: parameters passed contain NULLpointer\n");
		return SLL_NULL_POINTER;
	}
	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Loop until the end of the list or a match is found
	while (current != NULL)
	{
		// Compare the employee name with the given name (case-insensitive)
		if (!strcmpi(current->employeeData.name, name))
		{
			// Set the pointer to the found node
			*pointerToEmployeeNode = current;
			return SLL_NODE_FOUND;
		}
		// Move the pointer to the next node
		current = current->next;
	}
	// If no match is found, return an error code
	return SLL_NODE_NOT_FOUND;
}

// Print the data of an employee in a formatted way
void SLL_print_employee(employee_t data)

{
	printf("\n______________________________________________________________________________________________________\n");
	printf("|               NAME                |    ID    |    AGE    |        TITLE            |    SALARY     |\n");
	printf("|___________________________________|__________|___________|_________________________|_______________|\n");
	printf("|%-30s     |%-10d|%-11d|%-25s|%-15.2f|\n", data.name, data.id, data.age, data.title, data.salary);
	printf("|___________________________________|__________|___________|_________________________|_______________|\n");
}

// Print the data of series in a formatted way
void SLL_print_sequence_employee(employee_t data)
{
	printf("|%-30s     |%-10d|%-11d|%-25s|%-15.2f|\n", data.name, data.id, data.age, data.title, data.salary);
}

// Print the entire list by calling the print employee function for each node
void SLL_print_list(SinglyLinkedList_t *list)
{
	// Check if the list pointer is NULL
	if (list == NULL)
	{
		printf("SLL_print_list: NULL list pointer is passed to the function on call\n");
		return;
	}

	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Loop until the end of the list
	printf("\n______________________________________________________________________________________________________\n");
	printf("|               NAME                |    ID    |    AGE    |        TITLE            |    SALARY     |\n");
	printf("|___________________________________|__________|___________|_________________________|_______________|\n");
	while (current != NULL)
	{
		// Print the current node's data
		SLL_print_sequence_employee(current->employeeData);
		// Move the pointer to the next node
		current = current->next;
	}
	printf("|___________________________________|__________|___________|_________________________|_______________|\n");
	// Check if the list is empty


	return;
}

// Modify the employee data of a node by the given id and return a status code
SLL_status_t SLL_modify_emplyee_by_id(SinglyLinkedList_t *list, int id, employee_t newData)
{
	// Check if the list pointer is NULL
	if (list == NULL)
	{
		printf("SLL_modify_emplyee_by_id: NULL list pointer is passed to the function on call\n");
		return SLL_NULL_POINTER;
	}
	if (list->size == 0)
	{
		printf("SLL_modify_emplyee_by_id: List is empty \n");
		return SLL_NULL_POINTER;
	}
	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Loop until the end of the list or a match is found
	while (current != NULL)
	{
		// Compare the employee id with the given id
		if (current->employeeData.id == id)
		{
			// Copy the new data to the node
			current->employeeData = newData;
			return SLL_MODIFICATION_IS_DONE;
		}
		// Move the pointer to the next node
		current = current->next;
	}
	// If no match is found, return an error code
	return SLL_NODE_NOT_FOUND;
}

// Delete a node by the given id and return a status code
SLL_status_t SLL_delete_node_by_id(SinglyLinkedList_t *list, int id)
{
	// Check if the list pointer is NULL
	if (list == NULL)
	{
		printf("SLL_delete_node_by_id: NULL list pointer is passed to the function on call\n");
		return SLL_NULL_POINTER;
	}
	if (list->size == 0)
	{
		printf("SLL_delete_node_by_id: List is empty \n");
		return SLL_NULL_POINTER;
	}
	// Declare two pointers to traverse the list and keep track of the previous node
	node_t *current = list->head;
	node_t *prev = current;
	// Check if the first node matches the id
	if (current->employeeData.id == id)
	{
		// Set the head of the list to the next node
		list->head = list->head->next;
		// Free the memory of the deleted node
		free(current);
		// Decrement the size of the list
		list->size--;
		return SLL_OK;
	}
	else
	{
		// Loop until the end of the list or a match is found
		while (current != NULL && current->employeeData.id != id)
		{
			// Move the pointers to the next nodes
			prev = current;
			current = current->next;
		}
	}
	// Check if the current pointer is NULL, meaning no match was found
	if (current == NULL)
	{
		printf("ERROR : Employee not found\n");
		return SLL_NODE_NOT_FOUND;
	}
	// Set the next pointer of the previous node to the next node of the current node
	prev->next = current->next;
	// Free the memory of the deleted node
	free(current);
	// Decrement the size of the list
	list->size--;
	return SLL_OK;
}

// Free the entire list and return a status code
SLL_status_t SLL_free_list(SinglyLinkedList_t *list)
{
	// Check if the list pointer is NULL
	if (list == NULL)
	{
		printf("SLL_delete_node_by_id: NULL list pointer is passed to the function on call\n");
		return SLL_NULL_POINTER;
	}
	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Loop until the end of the list
	while (current != NULL)
	{
		// Set the head of the list to the next node
		list->head = list->head->next;
		// Free the memory of the current node
		free(current);
		// Move the pointer to the next node
		current = list->head;
	}
	// Free the memory of the list structure
	free(list);
	return SLL_OK;
}

// Free the nodes of the list but keep the list structure and return a status code
SLL_status_t SLL_free_nodes_keep_list(SinglyLinkedList_t *list)
{
	// Check if the list pointer is NULL
	if (list == NULL)
	{
		return SLL_NULL_POINTER;
	}
	// Declare a pointer to traverse the list
	node_t *current = list->head;
	// Loop until the end of the list
	while (current != NULL)
	{
		// Set the head of the list to the next node
		list->head = list->head->next;
		// Free the memory of the current node
		free(current);
		// Move the pointer to the next node
		current = list->head;
	}
	// Set the head of the list to NULL
	list->head = NULL;
	// Set the size of the list to 0
	list->size = 0;

	return SLL_OK;
}
