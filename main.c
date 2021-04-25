#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char  cData;
} Item;
/*
*
*/
typedef struct
{
    /* TODO: ADD YOUR CODE HERE */
} Stack;
/*
*
*/
Stack * initialize()
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
int isEmpty(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
Item top(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
Item pop(Stack *s)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
void push(Stack *s, Item val)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
void infixToPostfix(char* infix, char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluatePostfix(char* postfix)
{
    /* TODO: ADD YOUR CODE HERE */
}
/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while((s1 = strstr(s1, "\n")) != NULL)
        *s1 = ' ';
}
/*
*
*/
int main()
{
    char infixExpr[256] = "";
    char postfixExpr[256] = "";
    printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    while(fgets(infixExpr, 255, stdin) != NULL)
    {
        replaceNewLineBySpace(infixExpr);
        infixToPostfix(infixExpr, postfixExpr);
        printf("Postfix : %s\n", postfixExpr);
        float result = evaluatePostfix(postfixExpr);
        printf("Result: %f\n\n", result);
        printf("Enter an expression you want to evaluate or Ctrl+Z to exit: ");
    }
    return 0;
}
