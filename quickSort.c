//TODO 思考返回条件
//TODO 思考 (l + r + 1) / 2 和 (l + r - 1) / 2 与左子树右子树函数调用参数的关系
//TODO 测试下面几个地方写等于行不行

#include <stdio.h>

void quickSort(int arr[], int l, int r)
{
    if (l >= r) //* 问题最后出在这里！
        return;
    int x = arr[(l + r - 1) / 2]; //* (l + r + 1) / 2 就是不行，但是问题是什么呢？
    int i = l - 1;
    int j = r + 1;
    while (i < j) //*第一个问题，i、j写成了l、r //这里是i < j 
    {
        do
            i++;
        while (arr[i] < x); //*第二个问题，这里丢了等于，就必定会丢一个元素 —— 不应该加这个等号！！
        do
            j--;
        while (arr[j] > x);
        if (i < j) //*问题在于少加了这个if
        {
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    quickSort(arr, l, j);
    quickSort(arr, j + 1, r);
    return;
}

int main()
{
    int n;
    scanf("%d", &n);
    int arr[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    quickSort(arr, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        printf("%d", arr[i]);
    }
    return 0;
}