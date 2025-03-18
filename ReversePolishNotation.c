/*
 * RPN.c - 将中缀表达式转换为后缀表达式（逆波兰表示法）
 * 
 * 实现思路：
 * 1. 使用栈来存储运算符
 * 2. 对输入的每个字符进行处理：
 *    - 如果是操作数，直接输出
 *    - 如果是运算符：
 *      > 当栈顶运算符优先级大于等于当前运算符时，弹出并输出
 *      > 将当前运算符入栈
 *    - 如果是左括号，直接入栈
 *    - 如果是右括号：
 *      > 弹出并输出栈中运算符直到遇到匹配的左括号
 * 3. 将栈中剩余运算符依次弹出并输出
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LENGTH 128

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

int priority(char operator)
{
    int priority = 0;
    switch (operator)
    {
    case '+':
    case '-':
        priority = 1;
        break;
    case '*':
    case '/':
        priority = 2;
        break;
    default:
        break;
    }
    return priority;
}

int transform(char *before, char *after)
{
    stack operators = NULL;
    int i = 0;
    int j = 0;
    char cur = 0;
    while (cur = before[i++])
    {
        switch (cur)
        {
        // TODO 处理运算符的部分
        case '+':
        case '-':
        case '*':
        case '/': //! 当前运算符是需要入栈的
            while ((operators != NULL) && priority(get(&operators)) >= priority(cur))
            {
                after[j++] = pop(&operators);
            }
            push(&operators, cur);
            break;
        //* 处理括号的部分
        case '{':
        case '[':
        case '(':
            push(&operators, cur);
            break;
        case '}':
            if (operators == NULL)
            {
                printf("Invalid expression\n");
                return 1;
            }
            if (get(&operators) == '{')
            {
                pop(&operators);
            }
            else
            {
                while (get(&operators) != '{')
                {
                    after[j++] = pop(&operators);
                }
                pop(&operators);
            }
            break;
        case ']':
            if (get(&operators) == '[')
            {
                pop(&operators);
            }
            else
            {
                while (get(&operators) != '[')
                {
                    after[j++] = pop(&operators);
                }
                pop(&operators);
            }
            break;
        case ')':
            if (get(&operators) == '(')
            {
                pop(&operators);
            }
            else
            {
                while (get(&operators) != '(')
                {
                    after[j++] = pop(&operators);
                }
                pop(&operators);
            }
            break;
            //* 处理操作数的部分
        default:
            after[j++] = cur;
            break;
        }
    }
    while (operators != NULL)
    {
        after[j++] = pop(&operators);
    }

    return 0;
}

int main()
{
    char before[LENGTH] = {0};
    char after[LENGTH] = {0};
    fgets(before, LENGTH, stdin);
    before[strcspn(before, "\n")] = '\0';

    transform(before, after);

    printf("%s", after);
    return 0;
}