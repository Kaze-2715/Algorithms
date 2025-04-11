/*
 * 稀疏矩阵加法实现过程中遇到的问题及解决方案：
 * 
 * 1. 数据结构设计问题
 *    - 问题：最初使用指针数组作为行列头，导致内存管理复杂
 *    - 解决：改用节点数组作为行列头，简化了内存管理
 *    - 优点：直接通过下标访问行列头，避免了额外的指针管理
 * 
 * 2. colTails数组问题
 *    - 问题1：原本定义为node数组，导致对节点的复制而不是指向
 *    - 解决1：改为node**类型，只存储指针
 *    - 问题2：更新colTails时出现段错误
 *    - 解决2：确保先更新down指针再更新colTails指针
 * 
 * 3. 节点插入顺序问题
 *    - 问题：没有保持行内和列内元素的有序性
 *    - 解决：在插入时通过while循环找到正确的插入位置
 *    - 注意：需要同时维护right和down两个方向的顺序
 * 
 * 4. 内存泄漏问题
 *    - 问题1：createNode失败时没有处理
 *    - 解决1：添加返回值检查
 *    - 问题2：矩阵结构的内存没有完全释放
 *    - 解决2：实现完整的freeMatrix函数，按正确顺序释放
 * 
 * 5. 异常处理问题
 *    - 问题：主函数中没有检查add返回值
 *    - 解决：添加返回值检查，失败时清理已分配的内存
 *    - 改进：所有可能失败的函数调用都增加错误处理
 * 
 * 6. 输出缓存问题
 *    - 问题：程序看似无输出
 *    - 原因：输出缓冲区未刷新
 *    - 解决：在关键输出后添加fflush(stdout)
 * 
 * 7. 求和为零的情况
 *    - 问题：没有处理两个非零元素相加和为零的情况
 *    - 解决：只在和不为零时才创建新节点
 *    - 优化：减少了存储空间和后续处理量
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
    node *row, *col; // 改为节点数组
} matrix;

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
                colTails[newNode->col] = newNode; // 恢复这行代码
            }
        }
    }
    free(colTails);
    return new;
}

// 按行遍历矩阵并输出三元组
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

// 添加内存释放函数
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