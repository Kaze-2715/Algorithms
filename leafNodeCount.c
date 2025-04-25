#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// * 速通解法
// int main()
// {
//     char string[100] = {0};
//     scanf("%s", string);
//     int len = strlen(string);
//     int count = 0;
//     for (int i = 0; i < len - 2; i++)
//     {
//         if (isupper(string[i]) && string[i + 1] == '#' && string[i + 2] == '#')
//         {
//             count++;
//         }
//      
//     }
//     printf("%d", count);
//     return 0;
// }

typedef struct tNode
{
    char data;
    struct tNode *left, *right;
    int OK;
} tNode, *tree;

tNode *createNode(char data)
{
    tNode *new = malloc(sizeof(tNode));
    new->data = data;
    new->OK = 0;
    new->left = NULL;
    new->right = NULL;
    return new;
}

typedef struct node
{
    tNode *cur;
    struct node *next;
} node, *stack;

stack initStack()
{
    stack new = malloc(sizeof(node));
    new->cur = NULL;
    new->next = NULL;
    return new;
}

void push(stack s, tNode *cur)
{
    node *new = malloc(sizeof(node));
    new->cur = cur;
    new->next = s->next;
    s->next = new;
    return;
}

tNode *pop(stack s)
{
    if (!s->next)
    {
        puts("Stack is empty!");
        return 0;
    }
    tNode *cur = s->next->cur;
    node *top = s->next;
    s->next = top->next;
    free(top);
    return cur;
}

int empty(stack s)
{
    return s->next ? 0 : 1;
}

tNode *get(stack s)
{
    return s->next ? s->next->cur : 0;
}

tree makeTree(char *string)
{
    if (!string || !string[0])
    {
        return NULL;
    }
    tree t = createNode(string[0]);
    tNode *cur = t;
    stack nodes = initStack();
    push(nodes, cur);
    int len = strlen(string);
    int i = 1;
    //? 判断如何优化
    while (i < len - 1)
    {
        while (string[i] != '#')
        {
            if (cur->OK)
            {
                cur->right = createNode(string[i++]);
                cur = cur->right;
            }
            else
            {
                cur->left = createNode(string[i++]);
                cur = cur->left;
            }
            push(nodes, cur);
        }
        cur = pop(nodes);
        cur->OK = 1;
        //cur = cur->right;
        i++;
    }
    return t;
}

void inOrder(tree t)
{
    if (!t)
    {
        return;
    }
    
    inOrder(t->left);
    printf("%c", t->data);
    inOrder(t->right);
    return;
}

int main()
{
    char string[100] = {0};
    scanf("%s", string);
    int len = 0;
    tree t = makeTree(string);

    inOrder(t);
    return 0;
}