#include <stdio.h>
#include <stdlib.h>

typedef struct element
{
    int row, col, value;
} element;

typedef struct matrix
{
    element *array;
    int rowCount, colCount, eleNum;
} matrix;

int compare(const void *a, const void *b)
{
    element *p = (element *)a;
    element *q = (element *)b;
    if (p->row != q->row)
    {
        return p->row - q->row;
    }
    else
    {
        return p->col - q->col;
    }
    
}

matrix *add(matrix A, matrix B)
{
    if (A.colCount != B.colCount || A.rowCount != B.rowCount)
    {
        puts("Not same type, can't add.");
        return NULL;
    }

    matrix *new = malloc(sizeof(matrix));
    new->eleNum = A.eleNum + B.eleNum;
    new->colCount = A.colCount;
    new->rowCount = A.rowCount;
    new->array = (element*)calloc(new->eleNum, sizeof(element));

    // *先写快速算法
    // *先排序
    qsort(A.array, A.eleNum, sizeof(element), compare);
    qsort(B.array, B.eleNum, sizeof(element), compare);

    //* 用双指针法遍历
    int ptrA = 0, ptrB = 0, ptrNew = 0;

    while (ptrA < A.eleNum && ptrB < B.eleNum)
    {
        element a = A.array[ptrA];
        element b = B.array[ptrB];
        if (a.row == b.row && a.col == b.col)
        {
            new->array[ptrNew].row = a.row;
            new->array[ptrNew].col = a.col;
            new->array[ptrNew++].value = a.value + b.value;
            ptrA++;
            ptrB++;
        }
        else if (a.row < b.row || a.row == b.row && a.col < b.col)
        {
            new->array[ptrNew].row = a.row;
            new->array[ptrNew].col = a.col;
            new->array[ptrNew++].value = a.value;
            ptrA++;
        }
        else
        {
            new->array[ptrNew].row = b.row;
            new->array[ptrNew].col = b.col;
            new->array[ptrNew++].value = b.value;
            ptrB++;
        }
    }
    
    while (ptrA < A.eleNum)
    {
        new->array[ptrNew].row = A.array[ptrA].row;
        new->array[ptrNew].col = A.array[ptrA].col;
        new->array[ptrNew++].value = A.array[ptrA++].value;
    }

    while (ptrB < B.eleNum)
    {
        new->array[ptrNew].row = B.array[ptrB].row;
        new->array[ptrNew].col = B.array[ptrB].col;
        new->array[ptrNew++].value = B.array[ptrB++].value;
    }

    new->eleNum = ptrNew;

    return new;
    //TODO 整理两个矩阵元素数组的行信息：每行个数、数组中起始位置

    //TODO 按元素搜索，有则相加，无则添加

    //TODO 重新排序

    //TODO 返回新矩阵
}

int main() {
    int m, n, t1, t2;
    scanf("%d %d %d %d", &m, &n, &t1, &t2);

    matrix A, B;
    A.rowCount = B.rowCount = m;
    A.colCount = B.colCount = n;
    A.eleNum = t1;
    B.eleNum = t2;

    // 为两个矩阵分配空间
    A.array = (element *)malloc(t1 * sizeof(element));
    B.array = (element *)malloc(t2 * sizeof(element));

    // 读取第一个矩阵的数据
    for (int i = 0; i < t1; i++) {
        scanf("%d %d %d", &A.array[i].row, &A.array[i].col, &A.array[i].value);
    }

    // 读取第二个矩阵的数据
    for (int i = 0; i < t2; i++) {
        scanf("%d %d %d", &B.array[i].row, &B.array[i].col, &B.array[i].value);
    }

    // 计算矩阵之和
    matrix *result = add(A, B);
    if (result == NULL) {
        // 清理内存并退出
        free(A.array);
        free(B.array);
        return 1;
    }

    // 输出结果矩阵
    for (int i = 0; i < result->eleNum; i++) {
        printf("%d %d %d\n", result->array[i].row, result->array[i].col, result->array[i].value);
    }

    // 释放内存
    free(A.array);
    free(B.array);
    free(result->array);
    free(result);

    return 0;
}