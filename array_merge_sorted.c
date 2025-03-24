/*
 * @Author: Zhao Fangming
 * @Date: 2025-03-15
 * @Description: 合并两个有序数组
 */

#include <stdio.h>

/*
 * @brief 输入数组元素
 * @param arr 待输入的数组
 * @param maxSize 数组最大容量
 * @return int 返回实际输入的数组长度（0 <= 返回值 <= maxSize）
 */
int inputArray(int arr[], int maxSize)
{
    int len;
    do
    {
        scanf("%d", &len);
    } while (len > maxSize);

    for (int i = 0; i < len; i++)
    {
        scanf("%d", &arr[i]);
    }
    return len;
}

/*
 * @brief 合并两个有序数组
 * @param arr1 第一个有序数组
 * @param len1 第一个数组长度
 * @param arr2 第二个有序数组
 * @param len2 第二个数组长度
 * @param merged 合并后的数组
 * @return void 无返回值，结果直接存储在merged数组中
 */
void mergeSortedArrays(int arr1[], int len1, int arr2[], int len2, int merged[])
{
    int ptr1 = 0, ptr2 = 0, ptr3 = 0;

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

    while (ptr1 < len1)
    {
        merged[ptr3++] = arr1[ptr1++];
    }
    while (ptr2 < len2)
    {
        merged[ptr3++] = arr2[ptr2++];
    }
}

/*
 * @brief 打印数组元素
 * @param arr 待打印的数组
 * @param len 数组长度
 * @return void 无返回值，直接打印到标准输出
 */
void printArray(int arr[], int len)
{
    for (int i = 0; i < len; i++)
    {
        printf("%d\n", arr[i]);
    }
}

int main()
{
    int len1, len2;
    int arr1[20], arr2[20], merged[40];

    len1 = inputArray(arr1, 20);
    len2 = inputArray(arr2, 20);

    mergeSortedArrays(arr1, len1, arr2, len2, merged);
    printArray(merged, len1 + len2);

    return 0;
}