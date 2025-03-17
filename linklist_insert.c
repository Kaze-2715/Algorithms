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
        if (new == NULL)
        {
            printf("cannot allocate memory.\n");
            return 1;
        }

        new->data = number;
        new->next = list;

        list = new;
    }

    for (node *ptr = list; ptr != NULL; ptr = ptr->next)
    {
        printf("%i\n", ptr->data);
    }
}
