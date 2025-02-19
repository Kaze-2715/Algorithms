void selection_sort(int array[], int len)
{
    for (int i = 0; i < len - 1; i++)
    {
        int max = array[i];
        int index = i;
        for (int j = i + 1; j < len; j++)
        {
            if (max < array[j])
            {
                max = array[j];
                index = j;
            }
        }
        array[index] = array[i];
        array[i] = max;
    }
}

#include <stdio.h>  

void selection_sort(int array[], int len);

int arr[10] = {9, 8, 6, 1, 5, 3, 4, 2, 0, 7};

int main(void)
{
    int len = sizeof(arr) / sizeof(arr[0]);
    selection_sort(arr, len);
    for (int i = 0; i < 10; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
    return 0;
}