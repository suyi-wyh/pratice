// mysort.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//


#include"mysort.h"


void Swap(int* a, int* b)
{
	if (*a = *b)
		return;
	*a = *a ^ *b;
	*b = *a ^ *b;
	*a = *a ^ *b;
}


int* BubbleSort(int* data, int nums)   //冒泡排序
{
	for (int i = 0; i < nums - 1; ++i)
		for (int j = 0; j < nums - 1 - i; ++j)
		{
			if (data[j] > data[j + 1])
				Swap(&data[j],&data[j+1]);
		}
	return data;
}


int* InsertSort(int* data, int nums)   //插入排序
{
	for (int i = 1; i < nums; i++)
	{
		int cur = data[i];
		int j = i - 1;
		while (data[j] > cur && j >= 0)
		{
			data[j + 1] = data[j];
			j--;
		}
		data[++j] = cur;
	}
	return data;
}

  
int* SelectSort(int* data,int nums)     //选择排序
{
	for (int i = 0; i < nums - 1; ++i)
	{
		int cur = i;
		int j = i + 1;

		while (j < nums)
		{
			if (data[j] < data[cur])
				cur = j;
			j++;
		}
		if(cur != i)
			Swap(&data[cur], &data[i]);
	}
	return data;
}

int* ShellSort(int* data, int nums)
{
	int gap = nums;
	while (gap > 1)
	{
		gap = gap / 3 + 1;
		for (int i = 0; i < nums - gap; ++i)
		{
			int end = i;
			int tmp = data[end + gap];
			while (end >= 0)
			{
				if (tmp < data[end])
				{
					data[end + gap] = data[end];
					end -= gap;
				}
				else
					break;
			}
			data[end + gap] = tmp;
		}
	}
	return data;
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
