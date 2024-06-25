#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "history.h"

int main()
{
  char str[256];
  char userCommand;
  short len = 5;
  List *history = init_history();
  int id;
  

  /*Tokenizing is the proccess of dividing a string into tokens*/
  printf("Welcome to the Tokenizer!\n");
  printf("\n");

  while (1) {
    printf("Options:\n");
    printf("Enter a string = 's'\n");
    printf("Display history = 'h'\n");
    printf("Display specific item from history = '!'\n");
    printf("Quit = 'q'\n");
    printf("\n");
    printf("Enter your choice: ");
    scanf(" %c", &userCommand); //get user command input
    printf("\n");

    switch (userCommand) {
      case 's':
	printf("Enter a string: ");
	scanf(" %[^\n]", str); //get user string input
	add_history(history, str);
	printf("You entered: %s\n", str);

	char **tokens = tokenize(str);
	print_tokens(tokens);
	printf("\n");
	free_tokens(tokens); //free allocated tokens
	break;
	
      case 'h':
	printf("History of strings:\n");
	print_history(history);
	printf("\n");
	break;
	
      case '!':
	printf("Enter id:");
	scanf("%d", &id); // Read the sequence number directly after the '!'
	printf("\n");
	char *history_item = get_history(history, id);
	if (history_item) {
	  printf("History item %d: %s\n", id, history_item);
	  printf("\n");
	} else {
	  printf("No history item found with id: %d\n", id);
	  printf("\n");
	}
	break;
	
      case 'q':
	printf("Session ended. Goodbye!\n");
	printf("\n");
	free_history(history); // Free the history list and the strings it references
	return 0;
	
      default:
	printf("Invalid command. Try again.\n");
	break;
    }
  }

  
  
  return 0;
}
