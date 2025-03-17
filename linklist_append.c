#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
} node;

int main(int argc, char *argv[])
{
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *new = malloc(sizeof(node));

        new->data = number;
        new->next = NULL;

        if (list == NULL)
        {
            list = new;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (ptr->next == NULL)
                {
                    ptr->next = new;
                    break;
                }
            }
        }
    }

    for (node *ptr = list; list != NULL; ptr = ptr->next)
    {
        if (ptr != NULL)
        {
            printf("%i\n", ptr->data);
        }
        
    }
}