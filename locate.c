/*
 * 文件名: locate.c
 * 功能描述: 实现一个频率敏感的双向循环链表
 * 实现细节:
 * 1. 使用双向循环链表存储字符数据
 * 2. 每次查找某个字符时,该字符的访问频率+1
 * 3. 按照访问频率对链表节点进行冒泡排序,访问频率高的节点会移动到链表前端
 * 4. 最终输出排序后的链表内容
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node node, *list;
struct node
{
    char data;
    node *prev;
    node *next;
    int freqency;
};

int initList(list *List, int size)
{
    for (int i = 0; i < size; i++)
    {
        node *new = malloc(sizeof(node));
        scanf("%c", &new->data);
        getchar();
        new->freqency = 0;
        if (*List == NULL)
        {
            *List = new;
            new->next = new;
            new->prev = new;
        }
        else
        {
            node *tail = (*List)->prev;
            new->next = tail->next;
            tail->next = new;
            new->prev = tail;
            (*List)->prev = new;
        }
    }
    return 0;
}

int locate(list *List, char toLocate)
{
    // 查找操作
    node *ptr = *List;
    while (ptr != NULL)
    {
        if (ptr->data == toLocate)
        {
            ptr->freqency++;
            break;
        }
        ptr = ptr->next;
    }

    // 冒泡
    while (ptr != *List)
    { //! 交换的时候要整个节点赋值！
        if (ptr->freqency > ptr->prev->freqency)
        {
            char tmp = ptr->data;
            ptr->data = ptr->prev->data;
            ptr->prev->data = tmp;

            int freq = ptr->freqency;
            ptr->freqency = ptr->prev->freqency;
            ptr->prev->freqency = freq;
        }
        ptr = ptr->prev;
    }
    return 0;
}

int printList(list *List)
{
    node *ptr = *List;

    do
    {
        putchar(ptr->data);
        putchar(' ');
        ptr = ptr->next;
    } while (ptr != *List);
}

int main()
{
    // 结点数，待查数
    int nodeCount, toLocateCount;
    scanf("%d %d", &nodeCount, &toLocateCount);
    getchar();
    list new = NULL;
    initList(&new, nodeCount);
    // 循环查找
    for (int i = 0; i < toLocateCount; i++)
    {
        char toLocate = 0;
        scanf("%c", &toLocate);
        getchar();
        locate(&new, toLocate);
    }

    printList(&new);
}