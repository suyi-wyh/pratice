// work_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>

void yanghuisanjiao(int num)
{
    int a[10][10] = { 0 };
    a[0][0] = 1;
    for (int i = 1; i <= num; i++)
    {
        a[i][0] = 1;
        for (int j = 1; j <= i; j++)
            a[i][j] = a[i - 1][j - 1] + a[i - 1][j];  
    }
    for (int i = 0; i < num; i++)
    {
        for (int j = 0; j <= i; j++)
        {
            printf("%d  ", a[i][j]);
        }
        printf("\n");
    }
}

char Guess()
{

    for (char n = 'A'; n <= 'D'; n++)
    {
        if ((n != 'A') + (n == 'C') + (n == 'D') + (!(n == 'D')) == 3)
            return n;
    }
}

void GuessNum()
{
	for (int a = 1; a <= 5; a++)
		for (int b = 1; b <= 5; b++)
			for (int c = 1; c <= 5; c++)
				for (int d = 1; d <= 5; d++)
					for (int e = 1; e <= 5; e++)
                        if (((b == 2) + (a == 3) == 1)
                            && ((b == 2) + (e == 4) == 1)
                            && ((c == 1) + (d == 2) == 1)
                            && ((c == 5) + (d == 3) == 1)
                            && ((e == 4) + (a == 1) == 1))
                        {
                            if (a * b * c * d * e == 120)
                            {
                                printf("%d\n", a);
                                printf("%d\n", b);
                                printf("%d\n", c);
                                printf("%d\n", d);
                                printf("%d\n", e);
                            }
                        }
}
int main()
{
    yanghuisanjiao(9);
    printf("%c\n", Guess());
    printf("----------\n");
    GuessNum();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
