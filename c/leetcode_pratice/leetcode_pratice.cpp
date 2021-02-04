﻿// leetcode_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
/// <summary>
/// 634 子数组最大平均数
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="k"></param>
/// <returns></returns>
double findMaxAverage(int* nums, int numsSize, int k)
{
    double returnNums = 0;
    for (int i = 0; i < k; i++)
        returnNums += nums[i];
    returnNums = (double)returnNums / (double)k;
    double tmp = returnNums;
    for (int i = 0; i < numsSize - k; ++i)
    {
        tmp = (double)((double)(tmp * k) - (double)nums[i] + (double)nums[i + k]) / (double)k;
        if (returnNums < tmp)
            returnNums = tmp;
    }
    return returnNums;
}
/// <summary>
/// 
/// </summary>
/// <returns></returns>
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