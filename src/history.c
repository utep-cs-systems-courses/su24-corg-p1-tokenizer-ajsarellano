#include "history.h"
#include "stdio.h"
#include "stdlib.h"

/* Initialize the linked list to keep the history.*/
List* init_history() {
  List *list = malloc(sizeof(List)); //allocate memory for List structure

  if(list == NULL) {
    return NULL; // return NULL if memory allocation fails
  }
  
  list->root = NULL; //initialize list as empty because there's no items yet  
  return list;
}


/* Add a history item to the end of the list.
   List* list - the linked list
   char* str - the string to store*/
void add_history(List *list, char *str) {
  static int current_id = 0; // static variable to keep track of items

  Item *new_item = malloc(sizeof(Item)); //allocate memory for new item

  if(new_item == NULL) {
    return; //memory allocation fails
  }
  
  int len = 0;
  while(str[len] != '\0') { //calculate length of input string
    len++;
  }

  new_item->str = malloc((len + 1) * sizeof(char)); //allocate memory for new string
  if (new_item->str == NULL) {
    free(new_item); // Free the allocated memory for the item if string allocation fails
    return;
  }

  for (int i = 0; i <= len; i++) { // copy input string to new string
    new_item->str[i] = str[i];
  }

  new_item->id = current_id++; // Assign a unique ID to the new item
  new_item->next = NULL; // Initialize the next pointer to NULL

  // Find the last item in the list and add the new item
  if (list->root == NULL) {
    list->root = new_item; // If the list is empty, set the new item as the root
  } else {
    Item *current = list->root;
    while (current->next != NULL) { // Traverse to the end of the list and add new item
      current = current->next; 
    }
    current->next = new_item; // Add the new item at the end of the list
  }
}


/* Retrieve the string stored in the node where Item->id == id.
   List* list - the linked list
   int id - the id of the Item to find*/
char *get_history(List *list, int id) {
  Item *current = list->root; // start from root of list

  while (current != NULL) { //traverse list to find item with given id
    if (current->id == id) {
      return current->str; // return string if id matches
    }
    current = current->next; // move to next item
  }
}


/* Print the entire contents of the list.*/
void print_history(List *list) {
  Item *current = list->root; // start from root of list

  while (current != NULL) { // traverse the list
    //print id and string of current item
    printf("id: %d, str: %s\n", current->id, current->str);

    current = current->next;
  }
}

/* Free the history list and the strings it references.*/
void free_history(List *list) {
  Item *current = list->root; // start from root of list
  Item *next; //store next item before freeing current one

  while (current != NULL) {
    next = current->next; //save next item

    //free string associated with current item
    free(current->str);
    //free current item
    free(current);

    current = next; //move to next item
  }
  free(list); //free list structure
}
