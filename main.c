#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE 256
/*
* Item: An item that is being pushed to or popped from the stack
* It may be float (to be used while evaluating the postfix)
* It may be char (to be used while converting infix to postfix)
*/
typedef union
{
    float fData;
    char cData;
} Item;

/*array based
*/
typedef struct
{
    Item array[MAX_SIZE];
    int top;
} Stack;

/* It initializes stack so that there are no elements inserted.
*/
Stack *initialize()
{
    Stack *s = malloc(sizeof(Stack));
    s->top = 0;
    return s;
}

/*it checks if the top is empty or not so it can pop the elements and if the top equals 0 it will return 1
else it will return 0
*/
int isEmpty(Stack *s)
{
    if (s->top == 0)
        return 1;
    else
        return 0;
}

/*it checks if the top is equals to the MAX_SIZE and if it equals to the MAX_SIZE it will return 1
else it will return 0
*/
int isFull(Stack *s)
{
    if (s->top == MAX_SIZE)
        return 1;
    else
        return 0;
}

/*
*It inserts element at the top of the stack.
*/
Item top(Stack *s)
{
    return s->array[s->top - 1];
}

/*
*It removes the last inserted element in the stack and return it.
*/
Item pop(Stack *s)
{
    return s->array[--s->top];
}

/*
*It inserts element at the top of the stack.
*/
void push(Stack *s, Item val)
{
    s->array[s->top++] = val;
}
/*
* infixToPostfix: converts an expression in infix notation to
* to a postfix notation (Reverse-Polish Notation)
* ASSUME single-digit operands
* ASSUME ^*+-/ operators
* e.g., 22 + 31 --> 22 31 +
* e.g., ( 2 + 3 ) * 4 --> 2 3 + 4 *
*/
//Helping func used in infixToPostfix().
void err(char *message)
{
    printf("\n...%s...\n\n", message);
    exit(-1);
}

//Helping func used in lessPrec().
int prec(char c)
{
    switch (c)
    {
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
        return 2;
    case '^':
        return 3;
    default:
        return 0;
    }
}

//Helping func used in infixToPostfix().
int lessPrec(char ch1, char ch2)
{
    return prec(ch1) < prec(ch2);
}

//Helping func used in infixToPostfix()
int notValidType(char ch)
{
    if (!isdigit(ch) && ch != '.' && ch != '+' && ch != '-' && ch != '*' && ch != '/' && ch != '^' && ch != '(' &&
        ch != ')')
        return 1;
    else
        return 0;
}

//Helping func ised in infixToPostfix()
int isNegativeNumber(char ch, char oneCharBack, char twoCharBack)
{
    if (((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '(')) ||
        ((ch == '-') && (oneCharBack == '(')) ||
        ((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '+')) ||
        ((ch == '-') && (oneCharBack == '+')) ||
        ((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '-')) ||
        ((ch == '-') && (oneCharBack == '-')) ||
        ((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '*')) ||
        ((ch == '-') && (oneCharBack == '*')) ||
        ((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '/')) ||
        ((ch == '-') && (oneCharBack == '/')) ||
        ((ch == '-') && (oneCharBack == ' ') && (twoCharBack == '^')) ||
        ((ch == '-') && (oneCharBack == '^')))
        return 1;
    else
        return 0;
}

void infixToPostfix(char *infix, char *postfix)
{
    Stack *s = initialize();
    int index = 0;
    Item ch;
    /* To handle the case that the infix starts with a -ve number. If the string infix starts with '-' character,
      then this '-' character is not an operator. */
    if ((*infix) == '-')
    {
        postfix[index++] = '-';
        infix++;
    }
    while (ch.cData = *infix++)
    {
        if (ch.cData == ' ')
            continue;

        // Check that the ch.cData isn't a character, like a b c.....
        if (notValidType(ch.cData))
            err("Syntax Error...Characters are not allowed");

        // To handle -ve numbers inside brackets.
        if (isNegativeNumber(ch.cData, *(infix - 2), *(infix - 3)))
            postfix[index++] = '-';

        // To handle the digit cases.
        else if (isdigit(ch.cData))
        { // if the character after the scanned digit is '.' character, this means that we are scanning a float so we must keep scanning.
            if (*infix == '.')
            {
                postfix[index++] = ch.cData;
                postfix[index++] = '.';
                infix++;
            }
            /* If the character after the scanned character is digit, this means that we are either scanning a multi digit number
                  or the decimal part of a float number so we must keep scanning.*/
            else if (isdigit(*infix))
                postfix[index++] = ch.cData;
            // Else...we have completed the scanning of a number so we must add space after it to separate it from the next number or operator to be scanned.
            else
            {
                postfix[index++] = ch.cData;
                postfix[index++] = ' ';
            }
        }
        //If we found '(' character, we will push it to the stack.
        else if (ch.cData == '(')
            push(s, ch);
        //If we found ')' character, we will pop all the operator characters in the stack to the postfix string until we reach '(' and then pop that '(' character too.
        else if (ch.cData == ')')
        {
            while (top(s).cData != '(')
            {
                postfix[index++] = pop(s).cData;
                postfix[index++] = ' ';
                if (isEmpty(s))
                    err("Syntax Error...Missing '('");
            }
            pop(s);
        }
        /*If ch.cData higher precedence than top, then push the operator to the stack.
              If ch.cData less precedence than top, then pop all the operator characters in the stack to the postfix string
              and stop if stack empty or top == '(' and then push the operator to the stack.*/
        else //operator
        {
            if (lessPrec(ch.cData, top(s).cData))
            {
                while (!isEmpty(s) && top(s).cData != '(')
                {
                    postfix[index++] = pop(s).cData;
                    postfix[index++] = ' ';
                }
            }
            push(s, ch);
        }
    }
    while (!isEmpty(s)) // remaining operator characters in the stack.
    {
        if (top(s).cData == '(')
            err("\nSyntax Error...Missing ')'\n");
        postfix[index++] = pop(s).cData;
        postfix[index++] = ' ';
    }
    postfix[index] = 0;
}

/*
* Checks if a sting is an operand or not
* Return 1 if it's an operand else returns 0
*/
int isOperand(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}

/*
* Takes two Items and operand and perform the appropriate operation between  number
 */
Item performOperation(Item num1, Item num2, char operand)
{
    Item result;
    switch (operand)
    {
    case '+':
        result.fData = num2.fData + num1.fData;
        break;
    case '-':
        result.fData = num2.fData - num1.fData;
        break;
    case '*':
        result.fData = num2.fData * num1.fData;
        break;
    case '/':
        result.fData = num2.fData / num1.fData;
        break;
    case '^':
        result.fData = pow(num2.fData, num1.fData);
        break;
    }
    return result;
}

/*
* evaluatePostfix: Evaluates an expression in postfix notation
* (Reverse-Polish Notation)
*/
float evaluatePostfix(char *postfix)
{
    Stack *stack = initialize(); // initializes a new stack
    Item item;                   // holds the value of each character read from the postfix
    int index = 0;               // index of the buffer
    char buffer[256];            // temporarily holds numbers and operands

    // Reads through the postfix character by character
    while (item.cData = *postfix++)
    {
        // If it is a space
        if (item.cData == ' ')
        {
            // Stops the buffer at current index
            buffer[index] = '\0';

            // If it is a number
            if (!isOperand(buffer[index - 1]))
            {
                // converts string to float and push it to the stack
                item.fData = atof(buffer);
                push(stack, item);
            }
            // If it is an operand
            else if (isOperand(buffer[index - 1]))
            {
                // pops two numbers from the stack
                Item num1 = pop(stack);
                Item num2 = pop(stack);
                Item result = performOperation(num1, num2, buffer[index - 1]); // performs operation on two numbers
                push(stack, result); // pushes the result to the stack
            }
            index = 0; // Sets the index back to 0 inorder to reset the buffer
            continue;
        }
        // Splits the postfix by space and reads it into a buffer
        buffer[index++] = item.cData;
    }

    // Returns the result from the stack
    return pop(stack).fData;
}

/*
*
*/
void replaceNewLineBySpace(char *s)
{
    char *s1 = s;
    while ((s1 = strstr(s1, "\n")) != NULL)
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
    while (fgets(infixExpr, 255, stdin) != NULL)
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
