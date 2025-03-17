/*
 * @author Zhao Fangming
 * @brief  高精度计算pi值
 * @date Y2025-03-16
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// 定义链表节点结构和指针类型
typedef struct node node, *list;

// 双向链表节点结构体定义
struct node
{
    int data;   // 存储一个数字（0-9）
    node *prev; // 指向前一个节点
    node *next; // 指向后一个节点
};

// 计算需要的项数
int calculateItems(int digits)
{
    double add = 0.0;
    int items = 0;
    while (add < digits + 1)
    {
        items++;
        // 计算每一项对结果的贡献（以10为底的对数）
        add += log10((2.0 * items + 1) / items); //! 项数算错了！
    }

    return items;
}

// 创建链表节点
int createNode(list *List)
{
    // 采用头插法建表
    node *new = malloc(sizeof(node));
    new->data = 0;
    new->prev = NULL;
    if (*List == NULL)
    {
        *List = new;
        new->next = NULL;
    }
    else
    {
        new->next = *List;
        (*List)->prev = new; // !忘记将已有链表向前连接到新节点上了
        *List = new;
    }
    return 0;
}

// 初始化链表
int initList(list *List, int digits) // !初始化应该留三位有效数字！
{
    for (int i = 0; i < digits; i++)
    {
        createNode(List);
    }
    return 0;
}

// 打印pi值
int printPI(list *pi, int digits)
{
    node *ptr = *pi;
    int count = 0;
    while (ptr != NULL && (count < digits + 1))
    {
        if (count == 1)
        {
            printf(".");
        }
        printf("%d", ptr->data);
        ptr = ptr->next;
        count++;
    }
    return 0;
}

// 计算每一个要乘的系数的值
int calculateTerm(list *term, int termNumber)
{
    int numerator = termNumber;
    int denominator = (2 * termNumber + 1);
    node *ptr = *term;
    while (ptr != NULL)
    {
        ptr->data = numerator / denominator;
        numerator = 10 * (numerator % denominator);
        ptr = ptr->next;
    }
    return 0;
}

// 将当前项乘到结果中
int multiply(list *pi, list *term, list *result)
{
    node *ptrPi = *pi;
    node *ptrTerm = *term;
    node *ptrResult = *result;
    while (ptrPi->next != NULL)
    {
        ptrPi = ptrPi->next;
    }
    while (ptrTerm->next != NULL)
    {
        ptrTerm = ptrTerm->next;
    }
    while (ptrResult->next != NULL)
    {
        ptrResult = ptrResult->next;
    }
    node *piTail = ptrPi;         //* 求得pi的尾节点
    node *termTail = ptrTerm;     //* 求得系数的尾节点
    node *resultTail = ptrResult; //* 求得result的尾节点

    int position = 0; //* 标识这一轮运算从结果的第几位开始加
    while (ptrPi != NULL)
    {
        // *将结果的指针移到对应的起始位上
        for (int i = 0; i < position; i++)
        {
            ptrResult = ptrResult->prev;
        }
        // *取得当前这一位的因数
        int factor = ptrPi->data;
        // *遍历term列表，按位乘并进位
        while (ptrTerm != NULL && ptrResult != NULL)
        {
            // *先算出乘积，把这一位上的数字先加上去
            int product = factor * ptrTerm->data;
            ptrResult->data += product % 10;
            // !如果需要进位的话
            if (ptrResult->data >= 10) //! 进位条件是>=10
            {
                ptrResult->prev->data += ptrResult->data / 10;
                ptrResult->data = ptrResult->data % 10;
            }
            // *如果需要进位，下一位又存在的话，进位
            if (product >= 10 && ptrResult->prev != NULL)
            {
                ptrResult->prev->data += product / 10;
            }
            // *移动系数到下一位
            ptrTerm = ptrTerm->prev;
            // *移动结果到下一位
            ptrResult = ptrResult->prev;
        }
        // *当一位乘完之后，移动到下一位
        ptrPi = ptrPi->prev;
        // !将result复位
        ptrResult = resultTail;
        // !将Term复位
        ptrTerm = termTail;
        // * 更改标识符
        position++;
    }

    // !这里要从高位到低位地复制
    ptrPi = *pi; // 将指针重置到pi链表的头部，准备复制数据
    ptrResult = *result;
    while (ptrPi != NULL)
    {
        ptrPi->data = ptrResult->data;
        ptrPi = ptrPi->next;
        ptrResult = ptrResult->next;
    }
    // 将result链表清空
    ptrResult = *result;
    while (ptrResult != NULL)
    {
        ptrResult->data = 0;
        ptrResult = ptrResult->next;
    }
    return 0;
}

int main()
{
    int digits, termNumber;
    list pi = NULL;
    list term = NULL;
    list result = NULL;

    // 获取用户输入的位数
    scanf("%d", &digits);
    termNumber = calculateItems(digits);
    //初始化用于储存结果用的链表
    initList(&pi, digits + 3);
    initList(&term, digits + 3);
    initList(&result, 2 * digits + 5);
    pi->data = 1;
    // 循环进行先乘后加的操作来计算pi值
    for (int i = termNumber; i >= 1; i--)
    {
        calculateTerm(&term, i); //! 这里传参传错了！
        multiply(&pi, &term, &result);
        pi->data += 2;
    }

    printPI(&pi, digits);
    return 0;
}