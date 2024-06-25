#ifndef _TOKENIZER_
#define _TOKENIZER_


/* Return true(non-zero) if c is a tab or space, and not zero */
int space_char(char c);

/* Return true (non-zero) if c not a tab or space, and not zero*/ 
int non_space_char(char c);

/* Returns a pointer to the first character of the next 
   space-separated token in zero-terminated str.  Return a zero pointer if 
   str does not contain any tokens.*/
char *token_start(char *str); 

/* Returns a pointer terminator char following token */
char *token_terminator(char *token);

/* Counts the number of tokens in the string argument*/
int count_tokens(char *str);

/* Returns a fresly allocated new zero-terminated string 
   containing <len> chars from <inStr> */
char *copy_str(char *inStr, short len);

/* Returns a freshly allocated zero-terminated vector of freshly allocated 
   space-separated tokens from zero-terminated str.
   For example, tokenize("hello world string") would result in:

     tokens[0] = "hello"
     tokens[1] = "world"
     tokens[2] = "string" 
     tokens[3] = 0*/
char **tokenize(char* str);

/* Prints all tokens. */
void print_tokens(char **tokens);

/* Frees all tokens and the vector containing them. */
void free_tokens(char **tokens);

#endif
