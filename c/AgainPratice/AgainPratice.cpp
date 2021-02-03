// AgainPratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void Swap(int* a, int* b)
{
    if (a == b)
        return;
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

/// <summary>
/// 滑动窗口中位数
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>

void _Sort(int* nums, int numsSize)
{
    int gap = numsSize;
    while (gap > 1)
    {
        gap = gap / 3 + 1;
        for (int i = 0; i < numsSize - gap; i++)
        {
            int end = i;
            int tmp = nums[end + gap];

            while (end >= 0)
            {
                if (tmp < nums[end])
                {
                    nums[end + gap] = nums[end];
                    end -= gap;
                }
                else
                    break;
            }
            nums[end + gap] = tmp;
        }
    }
}


void QuickSort(int* data, int left, int right)
{
    if (left >= right)
        return;
    int mid = (left + right) / 2;
    // 三数取中
    if ((data[left] <= data[right] && data[right] <= data[mid])
        || (data[mid] <= data[right] && data[right] <= data[left]))
        Swap(&data[left], &data[right]);
    else if ((data[left] <= data[mid] && data[mid] <= data[right])
        || (data[right] <= data[mid] && data[mid] <= data[left]))
        Swap(&data[mid], &data[left]);
    //  三数取中
    int tmp = data[left];
    int nleft = left;
    int nright = right;
    while (left < right)
    {
        while (data[right] >= tmp && left < right)
            right--;
        while (data[left] <= tmp && left < right)
            left++;
        if (left < right)
            Swap(&data[left], &data[right]);
    }
    Swap(&data[nleft], &data[left]);
    QuickSort(data, nleft, left - 1);
    QuickSort(data, right + 1, nright);
}

void Sort(int* nums, int numsSize)
{
    int i = 0;
    while (i < numsSize)
    {
        int cur = i;
        for (int j = cur + 1; j < numsSize; j++)
        {
            if (nums[j] < nums[cur])
                cur = j;
        }
        Swap(&nums[cur], &nums[i]);
        i++;
    }
}

double* medianSlidingWindow(int* nums, int numsSize, int k, int* returnSize) {
    double* returnNums = (double*)malloc(sizeof(double) * numsSize);
    *returnSize = 0;
    int* stack = (int*)malloc(sizeof(int) * numsSize);
    int flag = 0;
    while (flag <= numsSize - k)
    {
        int j = 0;
        for (int i = flag; i < flag + k; i++, j++)
        {
            stack[j] = nums[i];
        }
        QuickSort(stack, 0, k - 1);
        if (k % 2 == 0)
            returnNums[flag] = ((double)stack[k / 2] + (double)stack[k / 2 - 1]) / 2;
        else
            returnNums[flag] = (double)stack[k / 2];
        flag++;
        (*returnSize)++;
    }
    return returnNums;
}
/// <summary>
/// 
/// </summary>
/// <param name="str"></param>
/// <param name="n"></param>
/// <returns></returns>
char* Sort(char* str,int n)
{

    for(int i=0;i<n-1;i++)
        for (int j = 1; j < n - i ; j++)
        {
            if (str[j-1] > str[j])
            {
                int tmp = str[j-1];
                str[j-1] = str[j];
                str[j] = tmp;
            }
        }
    return str;
}


void _Sort(int* nums, int numsSize)
{
    int i = 0;
    while (i < numsSize)
    {
        int cur = i;
        for (int j = cur + 1; j < numsSize; j++)
        {
            if (nums[j] < nums[cur])
                cur = j;
        }
        Swap(&nums[cur], &nums[i]);
        i++;
    }
}

int main()
{
 /*   char str[21];
    scanf("%s",str);
    int n = strlen(str);
    printf("%s\n", str);
    char* str1=Sort(str, n);
    for(int i=0;i<n;i++)
        printf("%c", str1[i]);*/
    int a = 1;
    int* x = &a;
    printf("%d\n", *x);
    *x++;
    printf("%d  ", *x);
    int nums[10] = {5,4,3,65,7,65,32,13,67,41};
    _Sort(nums, 10);
    for(int i=0;i<10;i++)
        printf("%d  ", nums[i]);
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
