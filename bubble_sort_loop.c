#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int arr[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    for (int i = 0; i < argc - 2; i++)
    {
        for (int j = 0; j < argc - i - 2; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                int tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}