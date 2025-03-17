/*
 * 文件功能：实现链表和数组的反转操作
 * 实现思路：
 * 1. 定义链表结构，包含数据和下一节点指针
 * 2. 提供三个主要函数：
 *    - reverseList: 反转链表
 *    - reverseArray: 反转数组
 *    - createNode: 创建并添加新节点到链表末尾
 * 3. 主程序流程：
 *    - 读取输入数据到链表和数组
 *    - 分别执行链表和数组的反转
 *    - 按要求格式输出结果
 *    - 释放内存
 */
#include <stdio.h>
#include <stdlib.h>

#define MAX 1000

typedef struct node node, *linkedlist;
struct node
{
    int data;
    node *next;
};

int reverseList(linkedlist *list)
{
    linkedlist tmp = NULL;
    node *ptr = *list;
    while (ptr != NULL)
    {
        if (tmp == NULL) //! first node
        {
            tmp = ptr;
            ptr = ptr->next;
            tmp->next = NULL;
            continue;
        }
        else
        {
            node *next = ptr->next;
            ptr->next = tmp; //! 指向节点的位置
            tmp = ptr;
            ptr = next;
        }
    }
    *list = tmp;
    return 0;
}

int reverseArray(int *array, int eleNum)
{
    for (int i = 0; i < eleNum / 2; i++)
    {
        int tmp = array[i];
        array[i] = array[eleNum - i - 1];
        array[eleNum - i - 1] = tmp;
    }
    return 0;
}

int createNode(int data, linkedlist *list)
{
    node *new = malloc(sizeof(node));
    new->data = data;
    new->next = NULL;

    if (*list == NULL)
    {
        *list = new;
        return 0;
    }
    else
    {
        node *ptr = *list;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = new;
        return 0;
    }
}

int main()
{
    int eleNum;
    linkedlist list = NULL;
    int *array = malloc(sizeof(int) * MAX);
    scanf("%d", &eleNum);

    for (int i = 0; i < eleNum; i++)
    {
        int tmp;
        scanf("%d", &tmp);
        createNode(tmp, &list);
        array[i] = tmp;
    }

    reverseList(&list);
    reverseArray(array, eleNum);

    for (int i = 0; i < eleNum; i++)
    {
        printf("%d", array[i]);
        if (i < eleNum - 1)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
    if (eleNum % 5 != 0)
    {
        printf("\n");
    }
    free(array);
    node *ptr = list;
    while (ptr != NULL)
    {
        node *next = ptr->next;
        printf("%d%s", ptr->data, next ? " " : "");
        free(ptr);
        ptr = next;
    }
}