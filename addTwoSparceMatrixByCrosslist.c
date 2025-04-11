/*
 * 文件名: addTwoSparceMatrixByCrosslist.c
 * 功能: 使用十字链表实现稀疏矩阵的加法运算
 * 作者: Zhao Fangming
 * 完成时间: 2025-04-12
 */

#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int col, row, data;
    struct node *right, *down;
} node;

typedef struct matrix
{
    int rowCount, colCount;
    node *row, *col;
} matrix;

/**
 * @brief 创建矩阵节点
 * @param row 行号
 * @param col 列号
 * @param data 节点数据
 * @return 返回新创建的节点指针
 */
node *createNode(int row, int col, int data)
{
    node *new = malloc(sizeof(node));
    new->row = row;
    new->col = col;
    new->data = data;
    new->down = NULL;
    new->right = NULL;

    return new;
}

/**
 * @brief 初始化十字链表矩阵
 * @param rowCount 矩阵行数
 * @param colCount 矩阵列数
 * @return 返回初始化的矩阵指针
 * @note 会分配行列头节点数组内存
 */
matrix *initMatrix(int rowCount, int colCount)
{
    matrix *new = malloc(sizeof(matrix));
    // 分配行头节点数组
    new->row = malloc(rowCount * sizeof(node));
    // 分配列头节点数组
    new->col = malloc(colCount * sizeof(node));
    new->rowCount = rowCount;
    new->colCount = colCount;

    // 初始化行头节点
    for (int i = 0; i < rowCount; i++)
    {
        new->row[i].row = i;
        new->row[i].col = -1;
        new->row[i].right = NULL;
        new->row[i].down = NULL;
    }

    // 初始化列头节点
    for (int j = 0; j < colCount; j++)
    {
        new->col[j].row = -1;
        new->col[j].col = j;
        new->col[j].right = NULL;
        new->col[j].down = NULL;
    }

    return new;
}

/**
 * @brief 十字链表矩阵加法
 * @param A 第一个矩阵指针
 * @param B 第二个矩阵指针
 * @return 返回结果矩阵指针，失败返回NULL
 * @note 维护行列的有序性
 */
matrix *add(matrix *A, matrix *B)
{
    if (A->colCount != B->colCount || A->rowCount != B->rowCount)
    {
        puts("Not same matrix");
        return NULL;
    }
    matrix *new = initMatrix(A->rowCount, A->colCount);

    node **colTails = malloc(new->colCount * sizeof(node *)); // 改为指针数组
    if (!colTails)
    {
        // 清理内存
        free(new->row);
        free(new->col);
        free(new);
        return NULL;
    }

    for (int i = 0; i < new->colCount; i++)
    {
        colTails[i] = &(new->col[i]); //?
    }

    for (int i = 0; i < new->rowCount; i++)
    {
        node *newNode = NULL;
        node *nodeA = A->row[i].right;
        node *nodeB = B->row[i].right;
        node *tail = &(new->row[i]);

        while (nodeA || nodeB)
        {
            newNode = NULL; // 重置newNode
            if (!nodeB || (nodeA && nodeA->col < nodeB->col))
            {
                newNode = createNode(i, nodeA->col, nodeA->data);
                nodeA = nodeA->right;
            }
            else if (!nodeA || (nodeB && nodeB->col < nodeA->col))
            {
                newNode = createNode(i, nodeB->col, nodeB->data);
                nodeB = nodeB->right;
            }
            else
            {
                int sum = nodeA->data + nodeB->data;
                if (sum != 0)
                {
                    newNode = createNode(i, nodeA->col, sum);
                }
                nodeA = nodeA->right;
                nodeB = nodeB->right;
            }

            if (newNode != NULL) // 只有在成功创建节点时才更新指针
            {
                tail->right = newNode;
                tail = tail->right;
                colTails[newNode->col]->down = newNode; //?
                colTails[newNode->col] = newNode;       // 恢复这行代码
            }
        }
    }
    free(colTails);
    return new;
}

/**
 * @brief 输出矩阵的三元组表示
 * @param m 待输出的矩阵指针
 * @note 按行主序输出
 */
void printTriples(matrix *m)
{
    for (int i = 0; i < m->rowCount; i++)
    {
        node *cur = m->row[i].right;
        while (cur)
        {
            printf("%d %d %d\n", cur->row, cur->col, cur->data);
            cur = cur->right;
        }
    }
}

/**
 * @brief 释放矩阵内存
 * @param m 待释放的矩阵指针
 * @note 会递归释放所有节点内存
 */
void freeMatrix(matrix *m)
{
    if (!m)
        return;

    for (int i = 0; i < m->rowCount; i++)
    {
        node *cur = m->row[i].right;
        while (cur)
        {
            node *next = cur->right;
            free(cur);
            cur = next;
        }
    }
    free(m->row);
    free(m->col);
    free(m);
}

int main()
{
    int m, n, t1, t2;
    scanf("%d %d %d %d", &m, &n, &t1, &t2);

    matrix *A = initMatrix(m, n);
    matrix *B = initMatrix(m, n);

    if (!A || !B)
    {
        freeMatrix(A);
        freeMatrix(B);
        return 1;
    }

    // 读取第一个矩阵的数据
    for (int i = 0; i < t1; i++)
    {
        int row, col, val;
        scanf("%d %d %d", &row, &col, &val);
        node *newNode = createNode(row, col, val);

        // 插入行链表
        node *rowPtr = &(A->row[row]);
        while (rowPtr->right && rowPtr->right->col < col)
        {
            rowPtr = rowPtr->right;
        }
        newNode->right = rowPtr->right;
        rowPtr->right = newNode;

        // 插入列链表
        node *colPtr = &(A->col[col]);
        while (colPtr->down && colPtr->down->row < row)
        {
            colPtr = colPtr->down;
        }
        newNode->down = colPtr->down;
        colPtr->down = newNode;
    }

    // 读取第二个矩阵的数据
    for (int i = 0; i < t2; i++)
    {
        int row, col, val;
        scanf("%d %d %d", &row, &col, &val);
        node *newNode = createNode(row, col, val);

        // 插入行链表
        node *rowPtr = &(B->row[row]);
        while (rowPtr->right && rowPtr->right->col < col)
        {
            rowPtr = rowPtr->right;
        }
        newNode->right = rowPtr->right;
        rowPtr->right = newNode;

        // 插入列链表
        node *colPtr = &(B->col[col]);
        while (colPtr->down && colPtr->down->row < row)
        {
            colPtr = colPtr->down;
        }
        newNode->down = colPtr->down;
        colPtr->down = newNode;
    }

    // 计算矩阵之和并输出
    matrix *result = add(A, B);
    if (!result)
    {
        freeMatrix(A);
        freeMatrix(B);
        return 1;
    }

    printTriples(result);
    fflush(stdout);

    // 释放内存
    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(result);

    return 0;
}