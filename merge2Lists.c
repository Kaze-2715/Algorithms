#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode
{
    int val;
    struct ListNode *next;
} node;

// 创建新节点的辅助函数
node *createNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// 打印链表的辅助函数
void printList(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d ", current->val);
        current = current->next;
    }
    printf("\n");
}

struct ListNode *mergeTwoLists(struct ListNode *list1, struct ListNode *list2)
{
    node *newList = NULL;
    if (list1 == NULL && list2 != NULL)
    {
        newList = list2;
        return newList;
    }
    if (list2 == NULL && list1 != NULL)
    {
        newList = list1;
        return newList;
    }
    if (list1 == NULL && list2 == NULL)
    {
        return NULL;
    }

    node *tail = NULL;
    node *next = NULL;
    if (list1->val > list2->val)
    {
        next = list2->next;
        list2->next = NULL;
        newList = list2;
        tail = list2;
        list2 = next;
    }
    else
    {
        next = list1->next;
        list1->next = NULL;
        newList = list1;
        tail = list1;
        list1 = next;
    }
    while (list1 != NULL && list2 != NULL)
    {
        if (list1->val > list2->val)
        {
            next = list2->next;
            list2->next = NULL;
            tail->next = list2;
            list2 = next;
        }
        else
        {
            next = list1->next;
            list1->next = NULL;
            tail->next = list1;
            list1 = next;
        }
        //! 更新尾节点
        tail = tail->next;
    }

    while (list1 != NULL)
    {
        next = list1->next;
        list1->next = NULL;
        tail->next = list1;
        list1 = next;
    }
    while (list2 != NULL)
    {
        next = list2->next;
        list2->next = NULL;
        tail->next = list2;
        list2 = next;
    }

    return newList;
}

int main()
{
    // 创建第一个测试链表: 1->2->4
    node *list1 = createNode(1);
    list1->next = createNode(2);
    list1->next->next = createNode(4);

    // 创建第二个测试链表: 1->3->4
    node *list2 = createNode(1);
    list2->next = createNode(3);
    list2->next->next = createNode(4);

    printf("列表1: ");
    printList(list1);
    printf("列表2: ");
    printList(list2);

    // 合并链表
    node *merged = mergeTwoLists(list1, list2);
    printf("合并后的列表: ");
    printList(merged);

    return 0;
}