/*
 * @Author: Zhao Fangming
 * @Date: 2025-03-15
 * @Description: 合并两个有序数组
 */

#include <stdio.h>

int main()
{
    int len1, len2;
    int arr1[20], arr2[20], merged[40]; // 两个输入数组和一个合并后的数组

    // 初始化第一个数组
    do
    {
        scanf("%d", &len1);
    } while (len1 > 20);
    

    for (int i = 0; i < len1; i++)
    {
        scanf("%d", &arr1[i]);
    }

    // 初始化第二个数组
    do
    {
        scanf("%d", &len2);
    } while (len2 > 20);
    

    for (int i = 0; i < len2; i++)
    {
        scanf("%d", &arr2[i]);
    }

    // 初始化指针
    int ptr1 = 0;
    int ptr2 = 0;
    int ptr3 = 0;

    // 先处理两个数组都有元素的情况
    //! 写成&&的问题是数组越界：如果出现了先遍历完了arr1，这时候再访问ptr1就会数组越界！
    while (ptr1 < len1 && ptr2 < len2)
    {
        if (arr1[ptr1] <= arr2[ptr2])
        {
            merged[ptr3++] = arr1[ptr1++];
        }
        else
        {
            merged[ptr3++] = arr2[ptr2++];
        }
    }

    // 处理剩余元素
    while (ptr1 < len1)
    {
        // 赋值后直接让变量自增
        merged[ptr3++] = arr1[ptr1++];
    }
    while (ptr2 < len2)
    {
        merged[ptr3++] = arr2[ptr2++];
    }

    // 输出合并后的数组
    for (int i = 0; i < len1 + len2; i++)
    {
        printf("%d\n", merged[i]);
    }
    return 0;
}