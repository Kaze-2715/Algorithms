#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

typedef struct node
{
    int value;
    int index;
    struct node *next;
} node;

node *hash[SIZE];

int insert(int value, int index)
{
    int key = value % SIZE;
    node *new = (node *)malloc(sizeof(node));
    new->value = value;
    new->index = index;
    new->next = hash[key];
    hash[key] = new;
    return 0;
}

int find(int value, int index)
{
    int key = value % SIZE;
    node *cur = hash[key];
    while (cur != NULL)
    {
        if (cur->value == value && cur->index != index)
        {
            return cur->index;
        }
        cur = cur->next;
    }
    return -1;
}

int compare(const void *a, const void *b)
{
    return *(int *)a - *(int *)b;
}

int **threeSum(int *nums, int numsSize, int *returnSize, int **returnColumnSizes)
{
    *returnSize = 0;
    int **result = (int **)malloc(sizeof(sizeof(int *)) * numsSize * numsSize);
    int resultCounter = 0;
    *returnColumnSizes = (int *)malloc(sizeof(int) * numsSize * numsSize);
    memset(*returnColumnSizes, 0, sizeof(int));
    int sizeCounter = 0;

    qsort(nums, numsSize, sizeof(int), compare);

    for (int i = 0; i < numsSize; i++)
    {
        // *策略一：外层循环去重
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int target = -nums[i];
        int left = i + 1;
        int right = numsSize - 1;

        while (left < right)
        {
            int sum = nums[left] + nums[right];
            if (sum == target)
            {
                result[*returnSize] = malloc(sizeof(int) * 3);
                result[*returnSize][0] = nums[i];
                result[*returnSize][1] = nums[left];
                result[*returnSize][2] = nums[right];
                (*returnColumnSizes)[*returnSize] = 3;
                (*returnSize)++;

                while (left < right && nums[left] == nums[left + 1])
                {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1])
                {
                    right--;
                }
                left++;
                right--;
            }
            else if (sum < target)
            {
                left++;
            }
            else
            {
                right--;
            }
        }
    }
    return result;
}

int main()
{
    // 初始化测试数组
    int nums[] = {-1, 0, 1, 2, -1, -4};
    int numsSize = sizeof(nums) / sizeof(nums[0]);
    int returnSize = 0;
    int *returnColumnSizes = NULL;

    // 初始化哈希表
    memset(hash, 0, sizeof(hash));

    // 调用 threeSum 函数
    int **result = threeSum(nums, numsSize, &returnSize, &returnColumnSizes);

    // 打印结果
    printf("找到 %d 组解:\n", returnSize);
    for (int i = 0; i < returnSize; i++)
    {
        printf("[%d,%d,%d]\n",
               result[i][0],
               result[i][1],
               result[i][2]);
    }

    // 释放内存
    for (int i = 0; i < returnSize; i++)
    {
        free(result[i]);
    }
    free(result);
    free(returnColumnSizes);

    return 0;
}