//* 速通广义表

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char string[100] = {0};
    int max = 0;
    int count = 0;
    scanf("%s", string);
    
    for (int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        if (c == '(')
        {
            count++;
        }
        if (c == ')')
        {
            count--;
        }
        max = count > max ? count : max;
    }
    
    printf("%d\n%d", max, max);
    return 0;
}