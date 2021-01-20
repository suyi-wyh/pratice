﻿// SList.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdlib.h>
#include<stdio.h>

typedef struct ListNode
{
    int data;
    struct ListNode* next;
}SList;

SList* CreatList(int num[],int n)
{
    SList* head, * last, * p;
    head = NULL;
    for (int i = 0; i < n; i++)
    {
        p = (SList*)malloc(sizeof(SList));
        p->data = num[i];
        p->next - NULL;
        if (head == NULL)
            head = last = p;
        else
           last = last->next = p;
    }
    return head;
}

int removeElement(int* nums, int numsSize, int val) 
{
    for (int i = 0; i < numsSize;)
    {
        if (*(nums + i) == val)
        {
            for (int j = i; j < numsSize - 1; j++)
            {
                *(nums + j) = *(nums + j + 1);
            }
            numsSize--;
        }
        else
            i++;
    }
    for (int i = 0; i < numsSize; i++)
        printf("%d ", *(nums + i));
    printf("\n%d", numsSize);
    return numsSize;
}

int removeDuplicates(int* nums, int numsSize) 
{
    for (int i = 0; i < numsSize-1;)
    {
        if (*(nums + i) == *(nums + i + 1))
        {
            for (int j = i + 1; j < numsSize - 1;++j)
            {
                *(nums + j) = *(nums + j + 1);
            }
            --numsSize;
        }
        else
            i++;
    }
    for (int i = 0; i < numsSize; i++)
        printf("%d ",*(nums+i));
    return numsSize;
}
int main()
{
    int nums1[] = { 1,1,2};
    int nums2[] = { 0,0,1,1,1,2,2,3,3,4  };
    int val1 = 3;
    int val2 = 2;
    //removeElement(nums2,8,val2);
    removeDuplicates(nums2,10);
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
