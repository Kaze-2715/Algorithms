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
        // initialize the new node
        int number = atoi(argv[i]);
        node *new = malloc(sizeof(node));
        new->data = number;
        new->next = NULL;

        // insert the noew node to the list
        if (list == NULL)
        {
            list = new;
        }
        else
        {
            for (node *ptr = list; ptr != NULL; ptr = ptr->next)
            {
                if (number <= ptr->data)
                {
                    if (ptr == list)
                    {
                        new->next = list;
                        list = new;
                        break;
                    }
                }
                else if (number > ptr->data)
                {
                    if (ptr->next == NULL)
                    {
                        ptr->next = new;
                        break;
                    }
                    else
                    {
                        if (number < ptr->next->data)
                        {
                            new->next = ptr->next;
                            ptr->next = new;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
    }
}