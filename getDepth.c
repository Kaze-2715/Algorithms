//* 标准解法

#include <stdio.h>
#include <string.h>

typedef enum
{
    ATOM,
    LIST
} Tag;

typedef struct atom
{
    char data;
} Atom;

typedef struct list
{
    struct list *head, *tail;
} List;

typedef struct node
{
    Tag tag;
    union
    {
        Atom atom;
        List list;
    } ptr;
} node, *GList;

GList makeList(char *string)
{

}

int main()
{
    char string[100] = {0};
    int count = 0;
    scanf("%s", string);
    GList new = makeList(string);
    int headDepth = getHeadDepth(new);
    int taiDepth = getTailDepth(new);
    printf("%d\n%d", headDepth, taiDepth);
    return 0;
}