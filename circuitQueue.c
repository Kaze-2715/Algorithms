/*
* 循环队列的一个题
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct queue queue;

struct queue
{
    int *array;
    int rear;
    int length;
    int size;
};

int initQueue(queue *Queue, int size)
{
    Queue->array = malloc(sizeof(int) * size);
    Queue->length = 0;
    Queue->rear = 0;
    Queue->size = size;

    return 0;
}

int isFull(queue *Queue)
{
    return (Queue->length == Queue->size) ? 1 : 0;
}

int enqueue(queue *Queue, int data)
{
    if (isFull(Queue))
    {
        return 1;
    }
    
    // TODO 入队
    Queue->array[Queue->rear] = data;
    Queue->rear = (Queue->rear + 1) % Queue->size;
    Queue->length++; // ! 长度记得递增
    return 0;
}

int dequeue(queue *Queue)
{
    //int front = (Queue->rear + Queue->length) % Queue->size; //! 取余数而不是整除
    int front = Queue->rear - Queue->length;
    if (front < 0)
    {
        front += Queue->size;
    }
    
    int toDequeue = Queue->array[front];
    Queue->length--;

    return toDequeue;
}

int printQueue(queue *Queue) //! 注意这个函数的逻辑!
{
    int front = Queue->rear - Queue->length;
    if (front < 0)
    {
        front += Queue->size;
    }
    for (int i = 0; i < Queue->length; i++)
    {
        int pos = (front + i) % Queue->size;
        printf("%d", Queue->array[pos]);
        if (i != Queue->length - 1)
        {
            printf(" ");
        }
    }
    puts("");
    return 0;
}

int get(queue *Queue)
{
    int front = Queue->rear - Queue->length;
    if (front < 0)
    {
        front += Queue->size;
    }
    return Queue->array[front];
}

int main()
{
    int length;
    queue Queue;
    scanf("%d", &length);
    getchar();
    initQueue(&Queue, length); //! 输入元素不一定等于队列容量！
    int data;
    // while (scanf("%d", &data) == 1) //! 判断条件！
    // {
    //     if (enqueue(&Queue, data))
    //     {
    //         break;
    //     }
    // }
    char input[128] = {0};
    fgets(input, sizeof(input), stdin); // 读取一行数据
    char *token = strtok(input, " \n");
    while (token != NULL)
    {
        int data = atoi(token);
        if (enqueue(&Queue, data))
        {
            printf("Queue is full. Cannot enqueue more elements.\n");
            break;
        }
        token = strtok(NULL, " \n");
    } //! 学着点怎么做任意数量输入
    int toDequeue;
    scanf("%d", &toDequeue);
    printf("%s\n", isFull(&Queue) ? "yes" : "no");
    
    while (dequeue(&Queue) != toDequeue)
    {
        continue;
    }
    printQueue(&Queue);

    printf("%d", get(&Queue));

    return 0;
}