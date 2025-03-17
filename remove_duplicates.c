/*
 * @brief 删除序列中的重复元素
 * 
 * 这个程序实现以下功能：
 * - 接收三个整数序列的输入
 * - 找出第二和第三个序列中的重复元素
 * - 从第一个序列中删除这些重复元素
 * - 输出处理后的第一个序列
 * 
 * 主要使用动态内存分配和数组操作来实现功能
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int len[3];
    scanf("%d %d %d", &len[0], &len[1], &len[2]);
    int *array[3];
    for (int i = 0; i < 3; i++)
    {
        array[i] = malloc(sizeof(int) * len[i]);
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < len[i]; j++)
        {
            scanf("%d", &array[i][j]);
        }
    }
    int *repeat = malloc(sizeof(int) * (len[1] > len[2] ? len[1] : len[2]));
    int count = -1;

    for (int i = 0; i < len[1]; i++)
    {
        for (int j = 0; j < len[2]; j++)
        {
            if (array[1][i] == array[2][j])
            {
                repeat[++count] = array[1][i];
            }
        }
    }

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < len[0]; j++)
        {
            if (repeat[i] == array[0][j]) //! 删除的逻辑
            {
                memmove(array[0] + j, array[0] + j + 1, sizeof(int) * (len[0] - j));
                len[0]--;
            }
            
        }
        
    }
    
    for (int i = 0; i < len[0]; i++)
    {
        printf("%d ", array[0][i]);
    }
    
    return 0;
}