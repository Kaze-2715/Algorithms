/*
 * 文件名: SparseMatrixTranspose.c
 * 功能: 实现稀疏矩阵的快速转置算法
 * 作者: Zhao Fangming
 * 完成时间: 2025-04-12
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

/**
 * @brief 稀疏矩阵快速转置
 * @param before 转置前的矩阵
 * @param after 转置后的矩阵
 * @note 使用一趟扫描完成转置，时间复杂度O(n)
 *       n为非零元素个数
 */
void transpose(RLSMatrix before, RLSMatrix *after)
{
    if (before.eleNum == 0)
    {
        return;
    }

    //先进行信息的基本传递
    after->eleNum = before.eleNum;
    after->colCount = before.rowCount;
    after->rowCount = before.colCount;
    int *rowStartPosition = calloc(after->rowCount + 1, sizeof(int)); //! 注意这里的+1 //! 注意这里是after

    //进行行主序的提取
    int *colCount = calloc(before.colCount + 1, sizeof(int)); //! 注意数组的初始化问题
    for (int i = 0; i < before.eleNum; i++)
    {
        colCount[before.array[i].col]++;
    }
    rowStartPosition[0] = 0; // 从0开始
    for (int i = 1; i < after->rowCount; i++)
    { // 修改循环范围
        rowStartPosition[i] = rowStartPosition[i - 1] + colCount[i - 1];
    }

    //进行数组元素的填充
    for (int i = 0; i < after->eleNum; i++)
    {
        int beforeCol = before.array[i].col;
        int afterRow = rowStartPosition[beforeCol];
        // after->array[afterRow] = before.array[afterRow]; //! 这里不应该原样复制的
        after->array[afterRow].row = before.array[i].col; // 行列互换
        after->array[afterRow].col = before.array[i].row; // 行列互换
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
