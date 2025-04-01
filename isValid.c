#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct node
{
    char c;
    struct node *next;
} node, *stack;

int isEmpty(stack *signs)
{
    return (*signs == NULL) ? 1 : 0;
}

int push(stack *signs, char c)
{
    node *new = malloc(sizeof(node));
    new->c = c;
    new->next = (*signs);
    (*signs) = new;
    return 0;
}

char pop(stack *signs)
{
    if (*signs == NULL)
    {
        return 0;
    }
    node *toPop = (*signs);
    char c = toPop->c;
    (*signs) = (*signs)->next;
    free(toPop);
    return c;
}

char get(stack *signs)
{
    if (*signs == NULL)
    {
        return -1;
    }
    return (*signs)->c;
}

bool isValid(char *s)
{
    if (strlen(s) % 2 == 1)
    {
        return false;
    }
    stack signs = NULL;
    int ptr = 0;
    while (s[ptr])
    {
        char ch = s[ptr];
        switch (ch)
        {
        case '(':
        case '[':
        case '{':
            push(&signs, ch);
            break;
        case ')':
            char pair = get(&signs);
            if (pair == '(')
            {
                pop(&signs);
            }
            else
            {
                return false;
            }
            break;
        case ']':
            pair = get(&signs);
            if (pair == '[')
            {
                pop(&signs);
            }
            else
            {
                return false;
            }
            break;
        case '}':
            pair = get(&signs);
            if (pair == '{')
            {
                pop(&signs);
            }
            else
            {
                return false;
            }
            break;
        default:
            continue;
            break;
        }
        ptr++;
    }
    return isEmpty(&signs) ? true : false;
}

int main()
{
    char *test_cases[] = {
        "(){}[]", // 有效
        "{[]}",   // 有效
        "([)]",   // 无效
        "(]",     // 无效
        "{{{}",   // 无效
        ""        // 有效
    };

    int test_count = sizeof(test_cases) / sizeof(test_cases[0]);

    printf("\n测试结果:\n");
    printf("=====================================\n");
    for (int i = 0; i < test_count; i++)
    {
        // 执行测试
        bool result = isValid(test_cases[i]);
        // 立即打印结果
        printf("用例 %d: \"%s\" \t=> %s\n",
               i + 1,
               test_cases[i],
               result ? "有效" : "无效");
    }
    printf("=====================================\n");

    return 0;
}