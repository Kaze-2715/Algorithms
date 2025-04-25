#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node
{
    char c;
    struct node *next;
} node, *stack;

stack initStack()
{
    stack new = malloc(sizeof(node));
    new->c = 0;
    new->next = NULL;
    return new;
}

void push(stack s, char data)
{
    node *new = malloc(sizeof(node));
    new->c = data;
    new->next = s->next;
    s->next = new;
    return;
}

char pop(stack s)
{
    if (!s->next)
    {
        puts("Stack is empty!");
        return 0;
    }
    char data = s->next->c;
    node *top = s->next;
    s->next = top->next;
    free(top);
    return data;
}

int empty(stack s)
{
    return s->next ? 0 : 1;
}

char get(stack s)
{
    return s->next ? s->next->c : 0;
}

typedef struct tNode
{
    char data;
    struct tNode *left, *right;
} tNode, *tree;

tNode *createNode(char data)
{
    tNode *new = malloc(sizeof(tNode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;
}

tNode *addLeftChild(tNode *root, char data)
{
    tNode *new = malloc(sizeof(tNode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    root->left = new;
    return new;
}

tNode *addRightChild(tNode *root, char data)
{
    tNode *new = malloc(sizeof(tNode));
    new->data = data;
    new->left = NULL;
    new->right = NULL;

    root->right = new;
    return new;
}

// void parser(char *expression, tree *t, stack s)
// {
//     int len = strlen(expression);
//     //! 判断是否有子树
//     if (len == 0 || !isupper(expression[0]) && !expression[0] == '#')
//     {
//         return;
//     }
//     if (!(*t))
//     {
//         //将根结点添加
//         (*t) = createNode(expression[0]);
//     }
//     //! 判断是不是最小的子树
//     if (expression[5] == ')')
//     {
//         (*t)->left = createNode(expression[2]);
//         (*t)->right = createNode(expression[4]);
//         return;
//     }
    
//     //解析字符串到左子树根结点，递归调用
//     char left = expression[2];
//     if (isupper(left) || (left == '#'))
//     {
//         (*t)->left = createNode(left);
//         parser(expression + 2, &((*t)->left), s);
//     }

//     //继续解析到右节点，递归调用
//     char right = 0;
//     int i;
//     //! 注意这里越过了根结点和第一个左括号
//     for (i = 2; (i < len - 2) && (!right); i++)
//     {
//         char c = expression[i];
//         switch (c)
//         {
//         case '(':
//             push(s, '(');
//             break;
//         case ')':
//             char top = get(s);
//             if (top == '(')
//             {
//                 pop(s);
//             }
//             break;
//         case ',':
//             if (empty(s))
//             {
//                 right = expression[i + 1];
//             }
//             break;
//         default:
//             break;
//         }
//     }
//     if (isupper(right) || (right == '#'))
//     {
//         (*t)->right = createNode(right);
//         parser(expression + i, &((*t)->right), s);
//     }
    
//     return ;
// }

void preOrder(tree t)
{
    if (!t)
    {
        return;
    }
    printf("%c", t->data);
    preOrder(t->left);
    preOrder(t->right);
    return;
}

int main()
{
    char string[100] = {0};
    scanf("%s", string);
    //stack brackets = initStack();
    tree t = NULL;
    //parser(string, &t, brackets);
    parser(string, &t);
    preOrder(t);
    return 0;
}

//TODO 写树和栈的析构函数
