// SQLIST.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<stdlib.h>
#define initsize 100
typedef int Datatype;
typedef struct {
	Datatype* data;
	int n;
	int maxsize;
}seqlist;
void Init(seqlist* L)
{
	L->data = (Datatype*)malloc(sizeof(Datatype) * initsize);
	L->n = 0;
	L->maxsize = initsize;
}
void creat(seqlist* L, int n)
{
	for (int i = 0; i < n; i++)
	{
		scanf_s("%d", &(L->data[i]));
		L->n = n;
	}
}
void removemin(seqlist* L, int* count)
{
	int i, pos = 0;
	for (i = 2; i <= L->n; i++)
	{
		if (L->data[i - 1] < L->data[pos])
			pos = i - 1;
	}
	*count = L->data[pos];
	L->n--;
	L->data[pos] = L->data[L->n];
}
void show(seqlist L)
{
	for (int i = 0; i < L.n; i++)
	{
		printf("%-3d", L.data[i]);
	}
}
int main()
{
	int n, back;
	seqlist L;
	Init(&L);
	printf("创建的长度：");
	scanf_s("%d", &n);
	printf("请输入初始值：");
	creat(&L, n);
	printf("创建的顺序表是：\n");
	show(L);
	removemin(&L, &back);
	printf("\n最小值为：%d", back);
	printf("\n删除后的顺序表是：\n");
	show(L);
	system("pause");
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
