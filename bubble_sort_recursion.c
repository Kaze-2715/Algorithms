#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int *, int);

int main(int argc, char *argv[])
{
    int arr[argc - 1];
    for (int i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
    }

    bubble_sort(arr, argc - 1);

    for (int i = 0; i < argc - 1; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void bubble_sort(int *array, int len)
{
    int tmp;
    if (len <= 2)
    {
        if (array[0] > array[1])
        {
            tmp = array[0];
            array[0] = array[1];
            array[1] = tmp;
        }
    }
    else
    {
        for (int i = 0; i < len - 1; i++)
        {
            if (array[i] > array[i + 1])
            {
                tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
        bubble_sort(array, len - 1);
    }
}