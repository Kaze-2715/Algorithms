/*
 * 文件名: multiplyTwoSparceMatrixByCrosslist.c
 * 功能: 使用十字链表实现稀疏矩阵的乘法运算
 * 作者: Zhao Fangming
 * 完成时间: 2025-04-12
 */

#include <stdio.h>
#include <stdlib.h>

// 矩阵节点结构
typedef struct node
{
    int row, col, data;
    struct node *right, *down;
} node;

// 矩阵结构
typedef struct matrix
{
    int rowCount, colCount;
    node *row, *col; // 行列头节点数组
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
    new->right = new->down = NULL;
    return new;
}

/**
 * @brief 初始化稀疏矩阵
 * @param rowCount 矩阵行数
 * @param colCount 矩阵列数
 * @return 返回初始化的矩阵指针
 * @note 会分配行列头节点数组内存
 */
matrix *initMatrix(int rowCount, int colCount)
{
    matrix *new = malloc(sizeof(matrix));
    new->row = malloc(rowCount * sizeof(node)); // 修正：移除了多余的+1
    new->col = malloc(colCount * sizeof(node));
    new->rowCount = rowCount;
    new->colCount = colCount;

    // 初始化行头节点
    for (int i = 0; i < rowCount; i++)
    {
        new->row[i].row = i;
        new->row[i].col = -1;
        new->row[i].right = new->row[i].down = NULL;
    }

    // 初始化列头节点
    for (int j = 0; j < colCount; j++)
    {
        new->col[j].row = -1;
        new->col[j].col = j;
        new->col[j].right = new->col[j].down = NULL;
    }

    return new;
}

/**
 * @brief 矩阵乘法运算
 * @param A 左矩阵
 * @param B 右矩阵
 * @return 返回结果矩阵指针，失败返回NULL
 * @note A的列数必须等于B的行数
 */
matrix *multiply(matrix *A, matrix *B)
{
    if (A->colCount != B->rowCount)
    {
        return NULL; // 移除puts，直接返回NULL
    }

    matrix *result = initMatrix(A->rowCount, B->colCount);

    // 遍历A的每一行
    for (int i = 0; i < A->rowCount; i++)
    {
        // 遍历B的每一列
        for (int j = 0; j < B->colCount; j++)
        {
            int sum = 0;
            node *rowA = A->row[i].right;
            while (rowA != NULL)
            {
                node *colB = B->col[j].down;
                while (colB != NULL)
                {
                    if (rowA->col == colB->row)
                    {
                        sum += rowA->data * colB->data;
                    }
                    colB = colB->down;
                }
                rowA = rowA->right;
            }

            if (sum != 0)
            {
                node *newNode = createNode(i, j, sum);

                // 行链表插入（按列号排序）
                if (result->row[i].right == NULL || result->row[i].right->col > j)
                {
                    newNode->right = result->row[i].right;
                    result->row[i].right = newNode;
                }
                else
                {
                    node *curr = result->row[i].right;
                    while (curr->right != NULL && curr->right->col < j)
                    {
                        curr = curr->right;
                    }
                    newNode->right = curr->right;
                    curr->right = newNode;
                }

                // 列链表插入（按行号排序）
                if (result->col[j].down == NULL || result->col[j].down->row > i)
                {
                    newNode->down = result->col[j].down;
                    result->col[j].down = newNode;
                }
                else
                {
                    node *curr = result->col[j].down;
                    while (curr->down != NULL && curr->down->row < i)
                    {
                        curr = curr->down;
                    }
                    newNode->down = curr->down;
                    curr->down = newNode;
                }
            }
        }
    }

    return result;
}

/**
 * @brief 释放矩阵内存
 * @param m 待释放的矩阵指针
 * @note 会递归释放所有节点内存
 */
void freeMatrix(matrix *m)
{
    if (m == NULL)
        return;

    for (int i = 0; i < m->rowCount; i++)
    {
        node *curr = m->row[i].right;
        while (curr != NULL)
        {
            node *temp = curr;
            curr = curr->right;
            free(temp);
        }
    }

    free(m->row);
    free(m->col);
    free(m);
}

int main()
{
    int m, n, row, col, val;

    // 读取第一个矩阵
    scanf("%d %d", &m, &n);
    matrix *A = initMatrix(m, n);
    while (1)
    {
        scanf("%d %d %d", &row, &col, &val);
        if (row == 0 && col == 0 && val == 0)
            break;
        node *newNode = createNode(row - 1, col - 1, val); // 转换为0基索引

        // 插入行链表
        if (A->row[row - 1].right == NULL)
            A->row[row - 1].right = newNode;
        else
        {
            node *p = A->row[row - 1].right;
            node *prev = &A->row[row - 1];
            while (p != NULL && p->col < col - 1)
            {
                prev = p;
                p = p->right;
            }
            prev->right = newNode;
            newNode->right = p;
        }

        // 插入列链表
        if (A->col[col - 1].down == NULL)
            A->col[col - 1].down = newNode;
        else
        {
            node *p = A->col[col - 1].down;
            node *prev = &A->col[col - 1];
            while (p != NULL && p->row < row - 1)
            {
                prev = p;
                p = p->down;
            }
            prev->down = newNode;
            newNode->down = p;
        }
    }

    // 读取第二个矩阵
    scanf("%d %d", &m, &n);
    matrix *B = initMatrix(m, n);
    while (1)
    {
        scanf("%d %d %d", &row, &col, &val);
        if (row == 0 && col == 0 && val == 0)
            break;
        node *newNode = createNode(row - 1, col - 1, val);

        if (B->row[row - 1].right == NULL)
            B->row[row - 1].right = newNode;
        else
        {
            node *p = B->row[row - 1].right;
            node *prev = &B->row[row - 1];
            while (p != NULL && p->col < col - 1)
            {
                prev = p;
                p = p->right;
            }
            prev->right = newNode;
            newNode->right = p;
        }

        if (B->col[col - 1].down == NULL)
            B->col[col - 1].down = newNode;
        else
        {
            node *p = B->col[col - 1].down;
            node *prev = &B->col[col - 1];
            while (p != NULL && p->row < row - 1)
            {
                prev = p;
                p = p->down;
            }
            prev->down = newNode;
            newNode->down = p;
        }
    }

    // 计算乘积并输出结果
    matrix *C = multiply(A, B);
    if (C != NULL)
    {
        // 按照行号和列号顺序输出
        for (int i = 0; i < C->rowCount; i++)
        {
            node *p = C->row[i].right;
            while (p != NULL)
            {
                printf("%d %d %d\n", p->row + 1, p->col + 1, p->data);
                p = p->right;
            }
        }
    }

    freeMatrix(A);
    freeMatrix(B);
    freeMatrix(C);

    return 0;
}
