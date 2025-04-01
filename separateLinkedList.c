#include <stdio.h>
#include <stdlib.h>

struct ListNode
{
    int val;
    struct ListNode *next;
};

typedef struct ListNode node;

struct ListNode *partition(struct ListNode *head, int x)
{
    if (head == NULL)
    {
        return NULL;
    }
    node *ptr = head;
    node *less = NULL, *lessTail = NULL;
    node *greater = NULL, *greaterTail = NULL;

    while (ptr != NULL)
    {
        node *next = ptr->next;
        ptr->next = NULL;
        if (ptr->val >= x)
        {
            if (greater == NULL)
            {
                greater = ptr;
                greaterTail = ptr;
            }
            else
            {
                greaterTail->next = ptr;
                greaterTail = greaterTail->next;
            }
        }
        else
        {
            if (less == NULL)
            {
                less = ptr;
                lessTail = ptr;
            }
            else
            {
                lessTail->next = ptr;
                lessTail = lessTail->next;
            }
        }
        ptr = next;
    }
    lessTail->next = greater;
    head = less;
    return head;
}

// 创建新节点
node *createNode(int value)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}

// 打印链表
void printList(node *head)
{
    node *current = head;
    while (current != NULL)
    {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

int main()
{
    // 测试样例 1: 1->4->3->2->5->2
    node *head1 = createNode(1);
    head1->next = createNode(4);
    head1->next->next = createNode(3);
    head1->next->next->next = createNode(2);
    head1->next->next->next->next = createNode(5);
    head1->next->next->next->next->next = createNode(2);

    printf("测试样例 1\n");
    printf("原始链表: ");
    printList(head1);

    int x1 = 3;
    printf("以%d为分界值重新排列后: ", x1);
    head1 = partition(head1, x1);
    printList(head1);

    // 测试样例 2: 2->1
    node *head2 = createNode(2);
    head2->next = createNode(1);

    printf("\n测试样例 2\n");
    printf("原始链表: ");
    printList(head2);

    int x2 = 2;
    printf("以%d为分界值重新排列后: ", x2);
    head2 = partition(head2, x2);
    printList(head2);

    // 测试样例 3: 4->3->2->5->2
    node *head3 = createNode(4);
    head3->next = createNode(3);
    head3->next->next = createNode(2);
    head3->next->next->next = createNode(5);
    head3->next->next->next->next = createNode(2);

    printf("\n测试样例 3\n");
    printf("原始链表: ");
    printList(head3);

    int x3 = 3;
    printf("以%d为分界值重新排列后: ", x3);
    head3 = partition(head3, x3);
    printList(head3);

    return 0;
}

// struct ListNode *partition(struct ListNode *head, int x)
// {
//     if (head == NULL)
//     {
//         return head;
//     }
//     node *cur = head->next;
//     node *prev = head;
//     node *ptr = head;
//     //! 必须要根据下一个节点的状态来为当前结点赋值
//     //! 这里的问题是顺序不对
//     while (cur != NULL && cur->next != NULL)
//     {
//         node *next = cur->next;
//         if (cur->val < x)
//         {
//             //! 二傻子写的头插法顾头不顾腚
//             // prev->next = next;
//             // cur->next = head;
//             // head = cur;

//             prev->next = next;
//             if (ptr == head && head->val > x)
//             {
//                 cur->next = head;
//                 head = cur;
//             }
//             else
//             {
//                 cur->next = ptr->next;
//                 ptr->next = cur;
//                 ptr = cur;
//             }
//         }
//         prev = cur;
//         cur = next;
//     }
//     //! 两个元素的样例过不了
//     // if (cur->val < x)
//     // {
//     //     prev->next = NULL;
//     //     cur->next = ptr->next;
//     //     ptr->next = cur;
//     //     ptr = cur;
//     // }

//     if (cur->val < x)
//     {
//         prev->next = NULL;
//         if (ptr == head && head->val > x)
//         {
//             cur->next = head;
//             head = cur;
//         }
//         else
//         {
//             cur->next = ptr->next;
//             ptr->next = cur;
//                 }
//     }

//     //! 到此为止的问题是链表没有封口
//     return head;
// }