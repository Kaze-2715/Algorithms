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

// 创建新节点
node *createNode(int row, int col, int data)
{
    node *new = malloc(sizeof(node));
    new->row = row;
    new->col = col;
    new->data = data;
    new->right = new->down = NULL;
    return new;
}

// 初始化矩阵
matrix *initMatrix(int rowCount, int colCount)
{
    matrix *new = malloc(sizeof(matrix));
    new->row = malloc(rowCount * sizeof(node));  // 修正：移除了多余的+1
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

/*
 * 矩阵乘法函数
 * @param A 左矩阵
 * @param B 右矩阵
 * @return 结果矩阵，如果无法相乘则返回NULL
 * 要求：A的列数等于B的行数
 * 结果矩阵：行数等于A的行数，列数等于B的列数
 */
matrix *multiply(matrix *A, matrix *B)
{
    if (A->colCount != B->rowCount)
    {
        return NULL;  // 移除puts，直接返回NULL
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
            
            // 修改计算逻辑
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

// 主函数部分需要添加：
int main()
{
    int m, n, row, col, val;
    
    // 读取第一个矩阵
    scanf("%d %d", &m, &n);
    matrix *A = initMatrix(m, n);
    while (1)
    {
        scanf("%d %d %d", &row, &col, &val);
        if (row == 0 && col == 0 && val == 0) break;
        node *newNode = createNode(row - 1, col - 1, val);  // 转换为0基索引
        
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
    
    // 读取第二个矩阵（类似过程）
    scanf("%d %d", &m, &n);
    matrix *B = initMatrix(m, n);
    while (1)
    {
        scanf("%d %d %d", &row, &col, &val);
        if (row == 0 && col == 0 && val == 0) break;
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
    
    return 0;
}
