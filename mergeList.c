/*
 * @file mergeList.c
 * @brief 链表合并操作的实现
 * @details 本文件实现链表的基本数据结构和合并操作
 *          - 定义了链表节点结构体
 *          - 实现链表的创建、合并等基本操作
 *          - 用于处理有序链表的合并功能
 * @note 该实现主要用于学习链表操作和合并算法
 */

#include <stdio.h>
#include <stdlib.h>

// 定义链表节点结构
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// 创建新节点的函数
Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// 插入节点到链表末尾
void insertAtEnd(Node **head, int value)
{
    Node *newNode = createNode(value);
    if (*head == NULL)
    {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL)
    {
        temp = temp->next;
    }
    temp->next = newNode;
}

// 打印链表
void printList(Node *head)
{
    Node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

// 合并两个有序链表的函数声明
Node *mergeLists(Node *list1, Node *list2);

int main()
{
    int m, n, i, value;
    Node *listA = NULL, *listB = NULL;

    // 输入两个链表的长度
    scanf("%d %d", &m, &n);

    // 输入第一个链表
    for (i = 0; i < m; i++)
    {
        scanf("%d", &value);
        insertAtEnd(&listA, value);
    }

    // 输入第二个链表
    for (i = 0; i < n; i++)
    {
        scanf("%d", &value);
        insertAtEnd(&listB, value);
    }

    // 合并链表
    Node *mergedList = mergeLists(listA, listB);

    // 打印结果
    printList(mergedList);

    // 释放内存的代码可以在这里添加
    return 0;
}

// TODO: 在这里实现 mergeLists 函数
Node *mergeLists(Node *list1, Node *list2)
{
    // Node *ptr1 = list1;
    // Node *ptr2 = list2;
    Node *merged = NULL;
    // Node *tail = NULL;
    while ((list1 != NULL) && (list2 != NULL))
    {
        if (list1->data < list2->data)
        {
            Node *next1 = list1->next;
            if (merged == NULL)
            {
                merged = list1;
                // !设成空
                list1->next = NULL;
            }
            else
            {
                list1->next = merged;
                merged = list1;
            }
            list1 = next1;
        }
        else
        {
            Node *next2 = list2->next;
            if (merged == NULL)
            {
                merged = list2;
                list2->next = NULL;
            }
            else
            {
                list2->next = merged;
                merged = list2;
            }
            list2 = next2;
        }
    }

    while (list1 != NULL)
    {
        Node *next = list1->next;
        list1->next = merged;
        merged = list1;
        list1 = next;
    }

    while (list2 != NULL)
    { // ! 保存指针
        Node *next = list2->next;
        list2->next = merged;
        merged = list2;
        list2 = next;
    }

    return merged;
}