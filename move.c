#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//! 问题是奇数个元素时的处理!
//! 三次旋转法
int reverse(int *array, int length)
{
    for (int i = 0; i < length / 2; i++)
    {
        int tmp = array[i];
        array[i] = array[length - i - 1];
        array[length - i - 1] = tmp;
    }
    return 0;
}

int move(int *array, int length, int k)
{
    reverse(array, length);
    reverse(array, k);
    reverse(array + k, length - k);
    return 0;
}
//! 经典的错误，标准的零分
// int move(int *array, int length, int k)
// {
//     int tmp, new;
//     int ptr = 0;
//     int count = 0;
//     while (count < length)
//     {
//         new = (ptr + k + length) % length;
//         tmp = array[ptr];
//         array[ptr] = array[new];
//         array[new] = tmp;
//         count += 2;
//         ptr = (new + 1 + length) % length;
//     }
//     return 0;
// }

int main()
{
    int n, k;
    scanf("%d %d", &n, &k);
    int *array = malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    move(array, n, k);

    for (int i = 0; i < n - 1; i++)
    {
        printf("%d ", array[i]);
    }
    printf("%d", array[n - 1]);

    return 0;
}