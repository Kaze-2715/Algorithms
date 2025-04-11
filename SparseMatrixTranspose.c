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
} RLSMatrix;

void transpose(RLSMatrix before, RLSMatrix *after)
{
    if (before.eleNum == 0)
    {
        return;
    }

    // TODO 先进行信息的基本传递
    after->eleNum = before.eleNum;
    after->colCount = before.rowCount;
    after->rowCount = before.colCount;
    int *rowStartPosition = calloc(after->rowCount + 1, sizeof(int)); //! 注意这里的+1 //! 注意这里是after

    // TODO 进行行主序的提取
    int *colCount = calloc(before.colCount + 1, sizeof(int)); //! 注意数组的初始化问题
    for (int i = 0; i < before.eleNum; i++)
    {
        colCount[before.array[i].col]++;
    }
    rowStartPosition[0] = 0;  // 从0开始
    for (int i = 1; i < after->rowCount; i++) {  // 修改循环范围
        rowStartPosition[i] = rowStartPosition[i - 1] + colCount[i - 1];
    }

    // TODO 进行数组元素的填充
    for (int i = 0; i < after->eleNum; i++)
    {
        int beforeCol = before.array[i].col;
        int afterRow = rowStartPosition[beforeCol];
        //after->array[afterRow] = before.array[afterRow]; //! 这里不应该原样复制的
        after->array[afterRow].row = before.array[i].col;  // 行列互换
        after->array[afterRow].col = before.array[i].row;  // 行列互换
        after->array[afterRow].data = before.array[i].data;

        rowStartPosition[beforeCol]++;
    }

    free(colCount);
    free(rowStartPosition);
    return;
}

int main()
{
    RLSMatrix before = {0}, after = {0};

    // 读取矩阵维度
    scanf("%d %d", &before.rowCount, &before.colCount);

    // 读取三元组
    before.eleNum = 0;
    int r, c, v;
    while (1)
    {
        scanf("%d %d %d", &r, &c, &v);
        if (r == 0 && c == 0 && v == 0)
            break;

        before.array[before.eleNum].row = r;
        before.array[before.eleNum].col = c;
        before.array[before.eleNum].data = v;
        before.eleNum++;
    }

    transpose(before, &after);

    // 输出转置后的结果
    for (int i = 0; i < after.eleNum; i++)
    {
        printf("%d %d %d\n",
               after.array[i].row,
               after.array[i].col,
               after.array[i].data);
    }

    return 0;
}
