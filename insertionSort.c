#include <stdio.h>

int insertionSort(int array[], int length);

int main()
{
    int n;
    printf("Length of array: ");
    scanf("%d", &n);
    int array[n];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &array[i]);
    }

    insertionSort(array, n);

    return 0;
}

int insertionSort(int array[], int length)
{
    for (int i = 1; i < length; i++)
    {
        for (int j = i - 1; j >= 0 && array[j] > array[j + 1]; j--)
        {
            int temp = array[j];
            array[j] = array[j + 1];
            array[j + 1] = temp;
        }
    }

    return 0;
}