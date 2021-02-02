// no2.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define MAXSIZE 5
#define OVERFLOW -1
#define OK 1
#define listIncrement 2
#define num_stop -1
typedef int elemType;

typedef struct
{
	elemType* elem;
	int length;
	int listsize;
}Sqlist;
int initList(Sqlist& list)
{
	list.elem = new int[MAXSIZE];
	if (!list.elem)
		exit(OVERFLOW);
	list.length = 0;
	list.listsize = MAXSIZE;
	return OK;
}
int ListInsert(Sqlist& list, int i, int num)
{
	int* newbase;
	if (i < 1)return ERROR;
	if (list.length == list.listsize)
	{
		newbase = (int*)realloc(list.elem, (list.listsize + listIncrement) * sizeof(int));
		if (!newbase)
			exit(OVERFLOW);
		list.elem = newbase;
		list.listsize += listIncrement;
	}
	list.elem[i - 1] = num;
	++list.length;
	return OK;
}
void printList(Sqlist list)
{
	for (int k = 0; k < list.length; k++)
		printf("%d ", list.elem[k]);
}
void deleteList(Sqlist& list, int num)
{
	int len = list.length;
	elemType* str = list.elem;
	int front = 0;
	while (front < len)
	{
		while (front < len && str[front] != num)
			front++;
		if (front < len)
			while (front < len && str[len] == num)
				len--;
		if (front < len)
		{
			str[front] = str[len - 1];
			front++;
			len--;
			list.length--;
		}
	}
}
int main()
{
	Sqlist list1;
	int flag;
	int num, count = 0;
	flag = initList(list1);
	printf("请输入若干数字,并以%d结束:", num_stop);
	scanf_s("%d", &num);
	count++;
	while (num != -1)
	{
		flag = ListInsert(list1, count, num);
		scanf_s("%d", &num);
		count++;
	}
	printList(list1); printf("\n");
	printf("需要删除的数字为:");
	scanf_s("%d", &num);
	deleteList(list1, num);
	printf("删除后的线性表为:");
	printList(list1);
	printf("\n");
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
