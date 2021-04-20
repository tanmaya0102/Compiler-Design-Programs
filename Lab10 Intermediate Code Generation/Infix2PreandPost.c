#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void insert(char ch);
void push(char symbol); 
char pop(); 
void displaypost(char * s);
int precedence(char ch); 
void intopostfix(char str[]);
struct Stack
{
    char data;
    struct Stack *next;
} *top = NULL, *pstart = NULL;



int main(int argc, char **argv)
{
    char str[50];
    char prefix_str[50];  //store postfix str
    char postfix_str[50]; //store prefix str
    printf("Enter infix expression: ");
    fgets(str, 50, stdin);
    str[strlen(str) - 1] = '\0';
    int i, j;

    for (i = strlen(str) - 1, j = 0; i >= 0; i--, j++)
    {
        if (str[i] == '(')
            prefix_str[j] = ')';
        else if (str[i] == ')')
            prefix_str[j] = '(';
        else
            prefix_str[j] = str[i];
    }
    prefix_str[j] = '\0';

    printf("\n\nEquivalent postfix expression is: ");
    intopostfix(str);
    displaypost(postfix_str);
    printf("%s", postfix_str);

    intopostfix(prefix_str);
    displaypost(prefix_str);
    //reverse prefix_str
    int temp;
    for (i = 0, j = strlen(prefix_str) - 1; i < j; i++, j--)
    {
        temp = prefix_str[i];
        prefix_str[i] = prefix_str[j];
        prefix_str[j] = temp;
    }
    printf("\n\nEquivalent prefix expression is: ");
    printf("%s\n", prefix_str);
    printf("\n");
    return 0;
}

/* function for insert operation */
void insert(char ch)
{

    struct Stack *ptr, *newNode;
    newNode = (struct Stack *)malloc(sizeof(struct Stack));
    newNode->next = NULL;
    newNode->data = ch;
    ptr = pstart;

    if (pstart == NULL)
    {
        pstart = newNode;
    }
    else
    {
        while (ptr->next != NULL)
            ptr = ptr->next;
        ptr->next = newNode;
    }
}

/* function for push operation */
void push(char symbol)
{

    struct Stack *ptr;

    ptr = (struct Stack *)malloc(sizeof(struct Stack));
    ptr->data = symbol;

    if (top == NULL)
    {
        top = ptr;
        ptr->next = NULL;
    }
    else
    {
        ptr->next = top;
        top = ptr;
    }
}

char pop()
{

    struct Stack *ptr1;
    char ch1;

    if (top == NULL)
    {
        printf("Stack underflow\n");
        return 0;
    }
    else
    {
        ptr1 = top;
        top = top->next;
        ch1 = ptr1->data;
        free(ptr1);
        ptr1 = NULL;
        return ch1;
    }
}

/* function for display display operation */
void displaypost(char *s)
{

    struct Stack *temp, *p;
    if (pstart == NULL)
        printf("");
    else
    {
        temp = pstart;
        int i = 0;
        while (temp != NULL)
        {
            p = temp;
            s[i] = temp->data; //store character in array
            temp = temp->next;
            free(p); //free storage
            i++;
        }
        s[i] = '\0';
    }
    pstart = NULL;
}

/*function for precedence */
int precedence(char ch)
{

    if (ch == '^')
    {
        return (5);
    }
    else if (ch == '*' || ch == '/')
    {
        return (4);
    }
    else if (ch == '+' || ch == '-')
    {
        return (3);
    }
    else
    {
        return (2);
    }
}
/*function for converting infix to postfix */
void intopostfix(char str[])
{

    int length;
    int index = 0;
    char symbol, temp;
    length = strlen(str);

    while (length > index)
    {
        symbol = str[index];

        switch (symbol)
        {

        case '(':
            push(symbol);
            break;

        case ')':
            temp = pop();

            while (temp != '(')
            {
                insert(temp);
                temp = pop();
            }

            break;

        case '^':
        case '+':
        case '-':
        case '*':
        case '/':

            if (top == NULL)
            {
                push(symbol);
            }
            else
            {
                while (top != NULL && (precedence(top->data) >= precedence(symbol)))
                {
                    temp = pop();
                    insert(temp);
                }
                push(symbol);
            }
            break;
        default:
            insert(symbol);
        }
        index = index + 1;
    }
    while (top != NULL)
    {
        temp = pop();
        insert(temp);
    }
    return;
}
/*function to convert infix to prefix */
void intoprefix(char str[])
{

    int length;
    int index = 0;
    char symbol, temp;
    length = strlen(str);

    while (length > index)
    {
        symbol = str[index];

        switch (symbol)
        {

        case ')':
            temp = pop();
            break;

        case '(':
            push(symbol);

            while (temp != ')')
            {
                insert(temp);
                temp = pop();
            }

            break;

        case '+':
        case '-':
        case '*':
        case '/':
        case '^':

            if (top == NULL)
            {
                push(symbol);
            }
            else
            {
                while (top != NULL && (precedence(top->data) <= precedence(symbol)))
                {
                    temp = pop();
                    insert(temp);
                }
                push(symbol);
            }
            break;
        default:
            insert(symbol);
        }
        index = index + 1;
    }
    while (top != NULL)
    {
        temp = pop();
        insert(temp);
    }
    return;
}