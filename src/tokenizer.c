#include "tokenizer.h"
#include "stdio.h"
#include "stdlib.h"

/* Return true (non-zero) if c is a tab or space, and not zero */
int space_char(char c)
{
  if(c == ' ' || c =='\t') { // check if c is a space or tab
    return 1;
  }
  return 0; // c is not a space or tab
}


/* Return true (non-zero) if c not a tab or space, and not zero*/
int non_space_char(char c)
{
  if(c != ' ' && c != '\t') { // check if c is not a space and not a tab
    return 1;
  }
  return 0; // c is a space, or tab
}


/* Returns a pointer to the first character of the next
   space-seperated token in zero-terminated str. Return a zero pointer if
   str does not contain any tokens.*/
char *token_start(char *str)
{
  int i = 0;
  while(*(str + i)) { //dereference pointer and continue loop as long as string is not NULL
    if(non_space_char(*(str + i))) { //check if current character is not a space
      return str + i; //return pointer to start of token
    }
    i++; //move to next character
  }
  return NULL; //contains no tokens(no non space characters)
}


/* Returns a pointer terminator char following *token */
char *token_terminator(char *token)
{
  int i = 0;
  while(*(token + i)) { //dereference pointer and continue loop as long as string is not NULL
    if(space_char(*(token + i))) { // check if current character is a space
        i++; // increment to move past space
	return token + i; //return next token
      }
      i++; //move to next character
  }
    return token + i;
}


/* counts the number of tokens in the string argument*/
int count_tokens(char *str)
{
  int count = 0;
  char *token = token_start(str); //find start of first token

  while(token != NULL) { //Loop while there's still tokens in string
    count++;
    token = token_terminator(token); //move to end of current token
    token = token_start(token); //find start of next token
  }
  return count; //return number of tokens
}


/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len)
{
  /*allocate memory for new string
    (len + 1) * sizeof(char) calculates number of bytes to allocate*/
  char *newStr = malloc((len + 1) * sizeof(char));

  if(newStr == NULL) { //check is memory allocation was successful, return if failed
    return NULL;
  }

  for (int i = 0; i < len; i++) { //copy characters up to len from inStri to newStr
    newStr[i] = inStr[i];
  }
  
  newStr[len] = '\0'; //make new string null terminated
  return newStr;
}


/* Returns a fresly allocated new zero-terminated string 
containing <len> chars from <inStr>
for example, tokenize("hello world string") would result in:
     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0*/
char **tokenize(char* str)
{
  int numTokens = count_tokens(str); //count number of tokens
  
  //alocate memory for array of token pointers
  char **tokens = malloc((numTokens + 1) * sizeof(char *)); 

  if (tokens == NULL) {
    return NULL; //memory allocation failed
  }

  int i = 0;
  char *token = token_start(str); //find start of first token

  while(token != NULL) { //iterate over each token
    char *end = token_terminator(token); //find end of current token
    int len = end - token; //calculate length of token

    tokens[i] = copy_str(token, len); //copy token to a new string
    i++;

    token = token_start(end); //find start of next token
  }

  tokens[i] = NULL; //terminate array with NULL pointer

  return tokens;
}


/* Prints all tokens. */
void print_tokens(char **tokens)
{
  int i = 0;

  while(tokens[i] != NULL) { //iterate through array of tokens
    printf("tokens[%d] = %s\n", i, tokens[i]);
    i++;
  }
}


/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens)
{
  int i = 0;
  while(tokens[i] != NULL) { //iterate through array of tokens 
    free(tokens[i]); //free allocated memory for current token
    i++;
  }
  free(tokens); //free allocated memory for array of tokens
}

