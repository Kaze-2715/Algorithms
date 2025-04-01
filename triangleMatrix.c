#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// @brief To compress an lower triangle matrix to a simple array then return it.
// @retval the pointer to the compressed array.
int *compress_Lower_Triangle_Matrix(int *matrix[], int size)
{
    if (matrix == NULL || size < 1)
    {
        return NULL;
    }

    // TODO 计算元素个数，分配空间
    int total = size * (size + 1) / 2; //! 元素个数是n * (n + 1)
    int *compressed = malloc(sizeof(int) * total);
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++) //! 只遍历下三角矩阵元素
        {
            int index = i * (i + 1) / 2 + j; //! 注意行标和列标的换算关系！这里的i换成i + 1; j 换成j + 1才是正确行标
            compressed[index] = matrix[i][j];
        }
    }
    return compressed;
}

int **decompress_Lower_Triangle_Matrix(int *compressed, int length)
{
    int size = (int)((-1 + sqrt(1 + 8 * length)) / 2);

    // 正确分配二维数组内存
    int **matrix = (int **)malloc(size * sizeof(int *));
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
        // 初始化该行所有元素为0
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }
    }

    // 填充下三角部分
    int index = 0;
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            matrix[i][j] = compressed[index++];
        }
    }

    return matrix;
}

int main()
{
    // 定义一个3x3的下三角矩阵
    int size = 3;
    int *matrix[3];
    for (int i = 0; i < size; i++)
    {
        matrix[i] = (int *)malloc(size * sizeof(int));
    }

    // 初始化下三角矩阵
    matrix[0][0] = 1;
    matrix[1][0] = 4;
    matrix[1][1] = 2;
    matrix[2][0] = 7;
    matrix[2][1] = 5;
    matrix[2][2] = 3;

    printf("=== 测试压缩和解压缩功能 ===\n");
    printf("1. 原始下三角矩阵：\n");
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }

    // 压缩矩阵
    int total = size * (size + 1) / 2;
    int *compressed = compress_Lower_Triangle_Matrix(matrix, size);

    // 打印压缩结果
    if (compressed != NULL)
    {
        printf("\n2. 压缩后的一维数组：\n");
        for (int i = 0; i < total; i++)
        {
            printf("%d ", compressed[i]);
        }
        printf("\n");

        // 测试解压缩
        printf("\n3. 解压缩后的矩阵：\n");
        int **decompressed = decompress_Lower_Triangle_Matrix(compressed, total);
        if (decompressed != NULL)
        {
            // 按矩阵形式打印解压缩结果
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < size; j++)
                {
                    if (j <= i)
                    {
                        printf("%d ", ((int **)decompressed)[i][j]);
                    }
                    else
                    {
                        printf("0 ");
                    }
                }
                printf("\n");
            }

            // 正确释放二维数组内存
            for (int i = 0; i < size; i++)
            {
                free(decompressed[i]);
            }
            free(decompressed);
        }

        // 释放压缩数组的内存
        free(compressed);
    }

    // 释放原始矩阵内存
    for (int i = 0; i < size; i++)
    {
        free(matrix[i]);
    }
    return 0;
}