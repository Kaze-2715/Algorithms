#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 729

struct ListNode
{
    int val;
    struct ListNode *next;
};

struct HashNode
{
    int value;
    struct ListNode *ptr;
    struct HashNode *next;
};

typedef struct HashNode node;

int find(node *hashtable[], struct ListNode *ptr, int value)
{
    //! 截断可能有问题
    int key = (uintptr_t)ptr % SIZE;
    node *hashPtr = hashtable[key];
    if (hashPtr == NULL)
    {
        return -1;
    }
    while (hashPtr != NULL)
    {
        if (hashPtr->ptr == ptr && hashPtr->value == value)
        {
            return key;
        }
        hashPtr = hashPtr->next;
    }
    return -1;
}

int insert(node *hashtable[], struct ListNode *ptr, int value)
{
    node *new = malloc(sizeof(node));
    new->ptr = ptr;
    new->value = value;
    int key = (uintptr_t)ptr % SIZE;
    new->next = hashtable[key];
    hashtable[key] = new;
    return 0;
}

bool hasCycle(struct ListNode *head)
{
    // !测试头指针是否为空
    if (head == NULL)
    {
        return false;
    }
    bool hasCycle = false;

    // *第一版循环
    // struct ListNode *slow = head;
    // struct ListNode *fast = slow->next;
    // while (fast != NULL && fast->next != NULL)
    // {
    //     if (slow == fast)
    //     {
    //         hasCycle = true;
    //         return hasCycle;
    //     }
    //     slow = slow->next;
    //     fast = fast->next->next;
    // }

    // *第二版循环
    // struct ListNode *slow = head;
    // struct ListNode *fast = head;
    // while (fast != NULL && fast->next != NULL)
    // {
    //     slow = slow->next;
    //     fast = fast->next->next;
    //     if (slow == fast)
    //     {
    //         return true;
    //     }
    // }

    //* 哈希表法
    //! 注意这里哈希表里面存的是指针的值
    node *hashTable[SIZE] = {NULL};
    struct ListNode *ptr = head;
    int count = 0;
    while (ptr != NULL)
    {
        int found = find(hashTable, ptr, ptr->val);
        if (found != -1)
        {
            return true;
        }
        insert(hashTable, ptr, ptr->val);
        ptr = ptr->next;
    }
    return false;

    // *歪点子1：特殊值法
    // struct ListNode *ptr = head;
    // while (ptr != NULL)
    // {
    //     if (ptr->val == INT_MAX)
    //     {
    //         return true;
    //     }
    //     ptr->val = INT_MAX;
    //     ptr = ptr->next;
    // }

    // *歪点子2：大循环法
    // struct ListNode *ptr = head;
    // for (int i = 0; i < 10001; i++)
    // {
    //     if (ptr == NULL)
    //     {
    //         return false;
    //     }
    //     ptr = ptr->next;
    // }
    // return hasCycle;
    // return true;
}

// 创建新节点的辅助函数
struct ListNode *createNode(int value)
{
    struct ListNode *node = (struct ListNode *)malloc(sizeof(struct ListNode));
    node->val = value;
    node->next = NULL;
    return node;
}

// 释放非环形链表内存
void freeList(struct ListNode *head)
{
    struct ListNode *current = head;
    while (current != NULL)
    {
        struct ListNode *temp = current;
        current = current->next;
        free(temp);
    }
}

int main()
{
    // 测试用例1：有环链表
    printf("测试用例1：有环链表\n");
    struct ListNode *head1 = createNode(3);
    head1->next = createNode(2);
    head1->next->next = createNode(0);
    head1->next->next->next = createNode(-4);
    head1->next->next->next->next = head1->next; // 创建环
    printf("结果：%s\n\n", hasCycle(head1) ? "有环" : "无环");

    // 测试用例2：无环链表
    printf("测试用例2：无环链表\n");
    struct ListNode *head2 = createNode(1);
    head2->next = createNode(2);
    head2->next->next = createNode(3);
    printf("结果：%s\n\n", hasCycle(head2) ? "有环" : "无环");
    freeList(head2);

    // 测试用例3：单节点链表
    printf("测试用例3：单节点链表\n");
    struct ListNode *head3 = createNode(1);
    printf("结果：%s\n\n", hasCycle(head3) ? "有环" : "无环");
    freeList(head3);

    return 0;
}