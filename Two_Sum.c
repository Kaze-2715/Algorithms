#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 100

int compare(const void *a, const void *b)
{
    return *((int *)a) - *((int *)b);
}

//* 双指针法
int *twoSum(int *nums, int numsSize, int target, int *returnSize)
{
    qsort(nums, numsSize, sizeof(int), compare);

    *returnSize = 0;
    int *result = NULL;
    int left = 0;
    int right = numsSize - 1;
    
    while (left < right)
    {
        int sum = nums[left] + nums[right];
        if (sum == target)
        {
            result = malloc(sizeof(int) * 2);
            result[0] = left;
            result[1] = right;
            *returnSize = 2;
            return result;
        }
        else if (sum < target)
        {
            left++;
        }
        else
        {
            right--; //! right--不是++
        }
        
    }
    return result;
}

// //* 哈希表解法
// typedef struct hashNode node;
// struct hashNode
// {
//     int value;
//     int index;
//     node *next;
// };

// node *hashTable[SIZE];

// int insert(int value, int index)
// {
//     int key = abs(value) % SIZE;
//     node *current = hashTable[key];
//     node *new = (node *)malloc(sizeof(node));
//     new->value = value;
//     new->index = index;
//     new->next = current;
//     //current = new; //! 插入有问题，修改的不是数组的元素值
//     hashTable[key] = new;
//     return 0;
// }

// int find(int value, int index)
// {
//     int key = abs(value) % SIZE;
//     node *current = hashTable[key];
//     while (current != NULL)
//     {
//         if (current->value == value && current->index != index)
//         {
//             return current->index;
//         }
//         current = current->next;
//     }
//     return -1;
// }

// int *twoSum(int *nums, int numsSize, int target, int *returnSize)
// {
//     int *index = NULL;
//     memset(hashTable, 0, sizeof(hashTable));

//     for (int i = 0; i < numsSize; i++)
//     {
//         int complement = target - nums[i];
//         int found = find(complement, i);
//         if (found != -1)
//         {
//             index = malloc(sizeof(int) * 2);
//             index[0] = found;
//             index[1] = i;
//             *returnSize = 2;
//             return index;
//         }
//         insert(nums[i], i);
//     }
//     *returnSize = 0;
//     return index;
// }

//* 暴力枚解法
// int *twoSum(int *nums, int numsSize, int target, int *returnSize)
// {
//     int *index = NULL;
//     for (int i = 0; i < numsSize - 1; i++)
//     {
//         for (int j = i + 1; j < numsSize; j++)
//         {
//             if (nums[i] + nums[j] == target)
//             {
//                 *returnSize = 2;
//                 index = malloc(sizeof(int) * 2);
//                 index[0] = i;
//                 index[1] = j;
//                 return index;
//             }
//         }
//     }
//     *returnSize = 0;
//     return index;
// }

    int main()
{
    // 测试用例1
    int nums1[] = {2, 7, 11, 15};
    int target1 = 9;
    int returnSize1;
    int *result1 = twoSum(nums1, 4, target1, &returnSize1);

    if (result1 != NULL)
    {
        printf("测试用例1结果: [%d, %d]\n", result1[0], result1[1]);
        free(result1);
    }

    // 测试用例2
    int nums2[] = {3, 2, 4};
    int target2 = 6;
    int returnSize2;
    int *result2 = twoSum(nums2, 3, target2, &returnSize2);

    if (result2 != NULL)
    {
        printf("测试用例2结果: [%d, %d]\n", result2[0], result2[1]);
        free(result2);
    }

    return 0;
}