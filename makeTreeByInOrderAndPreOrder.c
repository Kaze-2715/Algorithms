#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

tree makeTree(char *preOrder, char *inOrder, int len)
{
    if (len == 0)
    {
        return NULL;
    }
    if (len == 1)
    {
        tNode *new = createNode(preOrder[0]);
        return new;
    }
    // //! 这个不对
    // if (len == 3)
    // {
    //     tree new = createNode(preOrder[0]);
    //     new->left = createNode(preOrder[1]);
    //     new->right = createNode(preOrder[2]);
    //     return new;
    // }
    
    char root = preOrder[0];
    tree new = createNode(root);
    int inOrderRootIndex = 0;
    for (int i = 0; i < len; i++)
    {
        if (inOrder[i] == root)
        {
            inOrderRootIndex = i;
            break;
        }
        
    }
    int leftLen = inOrderRootIndex;
    int rightLen = len - inOrderRootIndex - 1;
    new->left = makeTree(preOrder + 1, inOrder + inOrderRootIndex - leftLen, leftLen);
    new->right = makeTree(preOrder + len - rightLen, inOrder + inOrderRootIndex + 1, rightLen);
    return new;
}

void postOrder(tree t)
{
    if (!t)
    {
        return;
    }
    postOrder(t->left);
    postOrder(t->right);
    printf("%c", t->data);
    return;
}

int main()
{
    char pre[100] = {0};
    char in[100] = {0};

    scanf("%s", pre);
    scanf("%s", in);

    tree t = makeTree(pre, in, strlen(pre));

    postOrder(t);
    return 0;
}
