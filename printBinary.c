#include <stdio.h>
#include <limits.h>

void printBinary(int number);

int main()
{
    int a = 0;
    printf("Number: ");
    scanf("%i", &a);

    printBinary(a);

    return 0;
}

// @brief 这个函数用来按位输出二进制数，输入任意数字都可以
// @retval 无返回值
void printBinary(int number)
{
    const int byteNumber = sizeof(int) * CHAR_BIT;
    for (int i = byteNumber - 1; i >= 0; i--)
    {
        printf("%d", ((number & (1 << i)) == 0) ? 0 : 1);
    }
    printf("\n");
    return;
}

//! 这个函数编写时出现的问题有：
//! 1.运算符优先级搞混了，“==”的优先级高于“&”
//! 2.循环次数输错了，最高位只需要左移31位即可

