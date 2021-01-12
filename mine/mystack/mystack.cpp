// mystack.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>

#define MAX 100

typedef char STACK_TYPE;
typedef struct Node
{
	STACK_TYPE* _number;
	int _top;
	int _capacity;
}stack;

void ChkStack(stack *stack)         //判断栈是否已满并扩容
{
	if (stack->_top == stack->_capacity - 1)
	{
		stack->_capacity *= 2;
		stack->_number = (STACK_TYPE*)realloc(stack->_number,stack->_capacity * sizeof(STACK_TYPE));
	}
}
int StackEmpty(stack* stack)
{
	if (-1 == stack->_top)
		return 0;
	else
		return stack->_top+1;
}
void StackInit(stack* stack)  //初始化栈
{
	stack->_number = (STACK_TYPE*)malloc(MAX * sizeof(STACK_TYPE));
	stack->_top = -1;
	stack->_capacity = MAX;
}

void StackPush(stack* stack,STACK_TYPE data)  //入栈
{
	ChkStack(stack);
	if (stack->_top < MAX - 1)
		stack->_number[++stack->_top] = data;
	else
		exit(0);
}

void StackPop(stack* stack)
{
	if (!StackEmpty(stack))
		printf("%d\n", stack->_number[stack->_top--]);
	else
		exit(0);
}
int StackTop(stack* stack) //获取栈中有效元素的个数
{
	return stack->_top - 1;
}

int StackDestroy(stack* stack)
{
	free(stack->_number);
	return 0;
}
int main()
{

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
