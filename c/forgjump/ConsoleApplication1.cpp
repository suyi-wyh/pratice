// ConsoleApplication1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>


#define max 10

int jump(int n)//青蛙跳台阶
{
    if (n < 3)
        return n;
    else
        return jump(n - 1) + (n - 2);
};


typedef struct stack {
    char p[max];
    int top;
}stack,Pa;


bool empty(Pa* S)
{
    if (S->top == 0)
        return true;
}
void push(Pa* S, char paren)
{
    S->p[S->top] = paren;
    S->top++;
}
void pop(Pa* S)
{
    S->top--;
}


bool Parentheses(Pa* S, char a[], int len)
{
    for (int i = 0; i < len; i++)
    {
        if (a[i] == '{')
            push(S, a[i]);
        if (a[i] == '}')
        {
            if (empty(S))
                return false;
            pop(S);
        }
    }
    if (empty(S))
        return true;
    else
        return false;
}

int main()
{
    stack* S=(stack *)malloc(sizeof(stack));
    S->top = 0;   
    char a[] = "{{{{}}}}" ;
    if (Parentheses(S, a, 9))
        printf("ok");
    else
        printf("no");
    return 0;
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
