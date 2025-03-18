/*
 * @file fibo.c
 * @description 使用循环队列计算k阶斐波那契数列
 * 
 * 实现思路:
 * 1. 使用循环队列存储k阶斐波那契数列的最后k个数
 * 2. 每次通过队列中现有的k个数计算下一个数
 * 3. 将最早的数出队,新数入队,直到计算得到的新数超过给定上限
 *
 * 核心功能:
 * - 实现了循环队列的基本操作(入队/出队/获取元素等)
 * - calculateNew()函数计算下一个斐波那契数
 * - 主函数实现了k阶斐波那契数列的生成逻辑
 *
 * k阶斐波那契数列定义:
 * - 前k-1项为0,第k项为1
 * - 之后每一项为前k项的和
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Queue Queue;

struct Queue
{
    int *array;
    int rear;
    int front;
    int size;
};

int initQueue(Queue *queue, int size)
{
    size++;
    queue->array = (int *)malloc(sizeof(int) * size);
    queue->rear = 0;
    queue->front = 0;
    queue->size = size;
    return 0;
}

int enqueue(Queue *queue, int data)
{
    if ((queue->rear + 1) % queue->size == queue->front)
    {
        puts("queue is full");
        return 1;
    }
    else
    {
        queue->array[queue->rear] = data;
        queue->rear = (queue->rear + 1) % queue->size;
    }
    return 0;
}

int dequeue(Queue *queue)
{
    int data = -1;
    if (queue->rear == queue->front)
    {
        puts("queue is empty");
    }
    else
    {
        data = queue->array[queue->front];
        queue->front = (queue->front + 1) % queue->size;
    }
    return data;
}

int get(Queue *queue)
{
    int data = -1;
    if (queue->rear == queue->front)
    {
        puts("queue is empty");
    }
    else
    {
        data = queue->array[queue->front];
    }
    return data;
}

int destroy(Queue *queue)
{
    free(queue->array);
    queue->array = NULL;
    queue->size = 0;
    queue->front = 0;
    queue->rear = 0;
    return 0;
}

int calculateNew(Queue *items)
{
    int newItem = 0;

    int ptr = items->front;
    while (ptr != items->rear)
    {
        newItem += items->array[ptr];
        ptr = (ptr + 1 + items->size) % items->size;
    }

    return newItem;
}

int printQueue(Queue *queue)
{
    int ptr = queue->front; 
    if (queue->front == queue->rear)
    {
        puts("queue is empty");
        return 0;
    }    
    while (ptr + 1 != queue->rear)
    {
        printf("%d ", queue->array[ptr]);
        ptr = (ptr + 1 + queue->size) % queue->size;
    }
    printf("%d", queue->array[ptr]);

    return 0;
}

int main()
{
    int rank, max;
    Queue items;
    scanf("%d %d", &max, &rank);

    initQueue(&items, rank);

    for (int i = 0; i < rank - 1; i++)
    {
        enqueue(&items, 0);
    }
    enqueue(&items, 1);

    int newItem = calculateNew(&items);
    while (newItem < max)
    {
        dequeue(&items);
        enqueue(&items, newItem);
        newItem = calculateNew(&items);
    }

    printQueue(&items);
    return 0;
}