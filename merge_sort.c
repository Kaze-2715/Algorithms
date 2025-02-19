#include <stdio.h>
#include <stdlib.h>

void merge_sort(int *array, int len);

int main(int argc, char *argv[])
{
    int arr[argc - 1];
    for (int i = 1; i < argc; i++)
    {
        arr[i - 1] = atoi(argv[i]);
    }

    merge_sort(arr, argc - 1);

    for (int i = 0; i < argc - 1; i++)
    {
        printf("%i ", arr[i]);
    }
    printf("\n");
}

void merge_sort(int *array, int len)
{
    if (len == 1)
    {
        return;
    }

    else if (len == 2)
    {
        int tmp = array[0];
        if (array[0] > array[1])
        {
            array[0] = array[1];
            array[1] = tmp;
            return;
        }
        else
        {
            return;
        }
        
    }
    
    else
    {
        int left_len = len / 2; //initialize the left half array
        int left[left_len];
        for (int i = 0; i < left_len; i++)
        {
            left[i] = array[i];
        }
        merge_sort(left, left_len); //sort the left half

        int right_len = len - len / 2; //initialize the right half array
        int right[right_len];
        for (int i = left_len; i < len; i++)
        {
            right[i - left_len] = array[i];
        }
        merge_sort(right, right_len); //sort the right half

        int arr_idx = 0;
        int left_idx = 0;
        int right_idx = 0;
        do
        {
            if (left[left_idx] < right[right_idx])
            {
                array[arr_idx] = left[left_idx];
                left_idx++;
                arr_idx++;
            }
            else
            {
                array[arr_idx] = right[right_idx];
                right_idx++;
                arr_idx++;
            }
        } while ((left_idx < left_len) && (right_idx < right_len));
        if (left_idx == left_len)
        {
            for (int i = right_idx; i < right_len; i++)
            {
                array[arr_idx] = right[i];
                arr_idx++;
            }
        }
        else if (right_idx == right_len)
        {
            for (int i = left_idx; i < left_len; i++)
            {
                array[arr_idx] = left[i];
                arr_idx++;
            }
        }
        return;
    }  
}