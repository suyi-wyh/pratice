// work.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<stdio.h>
#include<stdlib.h>

void Merge(int* num1, int m, int* num2, int n)
{
	int max = m + n - 1;
	int i = m - 1;
	int j = n - 1;
	while (i >= 0 && j >= 0)
	{
		if (*(num1 + i) > *(num2 + j))
		{
			*(num1 + max) = *(num1 + i);
			--i;
		}
		else
		{
			*(num1 + max) = *(num2 + j);
			--j;
		}
		--max;
	}
	while (i >= 0)
	{
		*(num1 + max) = *(num1 + i);
		max--;
		i--;
	}
	while (j >= 0)
	{
		*(num1 + max) = *(num2 + j);
		max--;
		j--;
	}
}

int Compare(int num[],int n)
{
	int x = 0;
	for (int i = 0; i < n; i++)
		x ^= num[i];
	return x;
}

void Delete(int num[],int n)
{
	int a;
	printf("需要删除多少个数字：\n");
	scanf_s("%d", &a);
	printf("请输入%d个数字:\n", a);
	int number[20];
	for (int i = 0; i < a; i++)
		scanf_s("%d", &number[i]);
	printf("\n");
	for (int j = 0; j < n; j++)
	{
		int f = 0;
		for (int i = 0; i < a; i++)
		{
			if (num[j] == number[i])
				f++;
		}
		if (0 == f)
			printf("%d ",num[j]);
	}
	printf("\n");
	printf("\n");
}
int* addToArrayForm(int* A, int ASize, int K, int* returnSize)
{
	int KSize = 0;
	int carrybit = 0, i = ASize - 1;
	int KNum = K;
	while (KNum)
	{
		++KSize;
		KNum /= 10;
	}
	int AKSize = (ASize > KSize ? ASize + 1 : KSize + 1);
	int qwe = AKSize;
	int* AK = (int*)malloc(AKSize * sizeof(int));
	while (AKSize-1)
	{
		int Y = K % 10;
		K /= 10;
		if (i >= 0)
		{
			*(AK + AKSize - 1) = Y + *(A + i) + carrybit;
			i--;
		}
		else
		{
			*(AK + AKSize - 1) = Y + carrybit;
		}
		if (*(AK + AKSize - 1) >= 10)
		{
			*(AK + AKSize - 1) = *(AK + AKSize - 1) % 10;
			carrybit = 1;
		}
		else
			carrybit = 0;
		--AKSize;
	}
	if (carrybit == 0)
	{
		AK = AK + 1;
		--qwe;
	}
	else
		*AK = 1;
	for (int aas = 0; aas < qwe; ++aas)
		printf("%d ", *(AK + aas));
	return returnSize;
}

int main()
{

	int A[] = { 8,2,3,4};
	int K = 4234;
	int ASize = 4;
	int* returnSize = (int *)1;
	addToArrayForm( A,ASize, K, returnSize);
	/*int num1[] = { 1,2,3,0,0,0 };
	int num2[] = { 2,5,6 };
	Merge(num1, 3, num2, 3);
	for (int i = 0; i < 6; i++)
		printf("%d  ", num1[i]);*/
	/*int xx[] = { 1,2,3,4,5,6,5,4,3,2,1 };
	printf("%d\n",Compare(xx,11));
	int a;
	printf("需要输入多少个数字：\n");
	scanf_s("%d",&a);
	printf("请输入%d个数字:\n", a);
	int num[20];
	for (int i = 0; i < a; i++)
		scanf_s("%d",&num[i]);
	printf("%d\n",a);
	for (int i = 0; i < a; i++)
		printf("%d ", num[i]);
	printf("\n");
	Delete(num,a);
	return 0;*/

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
