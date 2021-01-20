// stack()compare.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>

#define MAX 50

int ForgsStep(int stepsnum)
{
	if (1 == stepsnum)
		return 1;
	else if (2 == stepsnum)
		return 2;
	else
		return ForgsStep(stepsnum - 1) + ForgsStep(stepsnum - 2);
}

typedef struct comparestack
{
	char* top;
	char* base;
	int stacksize;
}stack;

stack* Initstack(stack *p)
{
	p->base = (char*)malloc(MAX*sizeof(stack));
	if (!p->base)
		exit(0);
	p->top = p->base;
	p->stacksize = MAX;
	return p;
}

int Push(stack* p, char x)
{
	if ((p->top) - (p->base) >= p->stacksize)
		exit(0);
	*(p->top) = x;
	(p->top)++;
	return 1;
}

int Pop(stack* p)
{
	if ((*p).top == (*p).base)
		exit(0);
	p->top--;
	printf("弹出%c\n", *(p->top));
	return 1;
}

int CheckingCompare(stack* p, char* chr)
{
	while (*chr != '\0')
	{
		if (*chr == '{')
			Push(p, *chr);
		else if (*chr == '}')
			Pop(p);
		chr++;
	}
	if (p->base == p->top)
		return 1;
	return 0;
}

int main()
{
	
	/*char* chr = "{fsd{fasd{ds{f{sf}sd}f}dsfs}f}sdfa";
	stack p;
	Initstack(&p);
	if (CheckingCompare(&p, chr))
		printf("okk");
	else
		printf("noo");*/

	printf("\n\n%d\n",ForgsStep(8));
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
