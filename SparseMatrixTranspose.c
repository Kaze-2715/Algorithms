/*
 * SparseMatrixTranspose.c - 稀疏矩阵转置算法实现
 *
 * 实现思路：
 * 1. 使用三元组表示稀疏矩阵：(行号,列号,值)
 * 2. 转置就是将三元组中的行列互换
 * 3. 按照新的列号（原行号）排序
 */

#define MAX 1000
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct element
{
    int row, col;
    int data;
} element;

typedef struct RLSMatrix
{
    element array[MAX];
    int rowCount, colCount, eleNum;
    int *rowStartPosition, *colStartPosition;
} RLSMatrix;

void transpose(RLSMatrix before, RLSMatrix after)
{
    if (before.eleNum == 0)
    {
        return;
    }
    
    //TODO 先进行信息的基本传递
    after.eleNum = before.eleNum;
    after.colCount = before.rowCount;
    after.rowCount = before.colCount;
    before.rowStartPosition = malloc(sizeof(int) * (before.rowCount + 1));//! 注意这里的+1


    //TODO 进行行主序的提取
    int *colCount = malloc(sizeof(int) * (before.colCount + 1));
    for (int i = 0; i < before.eleNum; i++)
    {
        colCount[before.array[i].col]++;
    }
    before.rowStartPosition[1] = 0;
    for (int i = 2; i < before.rowCount; i++)
    {
        before.rowStartPosition[i] = before.rowStartPosition[i - 1] + colCount[i - 1];
    }
    

    //TODO 进行数组元素的填充
    for (int i = 0; i < after.eleNum; i++)
    {
        int beforeCol = before.array[i].col;
        int afterRow = before.rowStartPosition[beforeCol];
        after.array[afterRow] = before.array[afterRow];

        before.rowStartPosition[beforeCol]++;
    }
    return;
}

int main()
{
    int row, col;
    char buffer[8] = {0};
    scanf("%d %d", &row, &col);
    RLSMatrix before, after;
    before.colCount = col;
    before.rowCount = row;
    before.colStartPosition = NULL;
    before.rowStartPosition = NULL;

    int i = 0;
    while (strcmp(gets(buffer), "0 0 0"))
    {
        sscanf(buffer, "%d %d %d", &before.array[i].row, &before.array[i].row, &before.array[i].data);
        before.eleNum++;
    }

    transpose(before, after);

    for (int i = 0; i < after.eleNum; i++)
    {
        printf("%d %d %d\n", after.array[i].row, after.array[i].col, after.array[i].data);
    }
    
    return 0;
}
