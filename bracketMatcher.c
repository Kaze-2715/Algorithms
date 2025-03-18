#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 1024

typedef struct node node, *stack;
struct node
{
    char data;
    node *next;
};

char push(stack *Stack, char ch)
{
    node *new = malloc(sizeof(node));
    new->data = ch;
    if (*Stack == NULL)
    {
        *Stack = new;
        new->next = NULL;
    }
    else
    {
        new->next = *Stack;
        *Stack = new;
    }
    return ch;
}

char pop(stack *Stack)
{
    node *toDelete = *Stack;
    char ch = toDelete->data;
    *Stack = toDelete->next;
    free(toDelete);
    return ch;
}

char get(stack *Stack)
{
    return (*Stack == NULL) ? 0 : (*Stack)->data;
}

int destroy(stack *Stack)
{
    node *next = NULL;
    while (*Stack != NULL)
    {
        next = (*Stack)->next;
        free(*Stack);
        *Stack = next;
    }
    return 0;
}

int matcher(char *string)
{
    stack signs = NULL;
    int i = 0;
    char ch;
    while (ch = string[i])
    {
        switch (ch)
        {
        case '{':
        case '(':
        case '[':
            push(&signs, ch);
            break;
        case ']':
            
            if (get(&signs) == '[')
            {
                pop(&signs);
            }
            else
            {
                push(&signs, ch);
            }
            break;
        case '}':
            if (get(&signs) == '{')
            {
                pop(&signs);
            }
            else
            {
                push(&signs, ch);
            }
            break;
        case ')':
            if (get(&signs) == '(')
            {
                pop(&signs);
            }
            else
            {
                push(&signs, ch);
            }
            break;
        default:
            break;
        }
        i++;
    }

    int flag = (signs == NULL) ? 1 : 0;
    destroy(&signs);
    return flag;
}

int main()
{
    char string[LENGTH] = "";
    fgets(string, 1024, stdin);
    char *newline = strpbrk(string, "\n");
    if (newline) *newline = '\0'; //! OJ平台的输入没有换行符！会报错！

    printf("%s\n", matcher(string) ? "yes" : "no");
    return 0;
}