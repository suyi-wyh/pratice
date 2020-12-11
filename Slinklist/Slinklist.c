// Slinklist.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <stdio.h>
#include<stdlib.h>

typedef int SLdatatype;

typedef struct node
{
    SLdatatype val;
    struct node* next;
}LINKList;

LINKList* Init(int a[],int n)
{
    LINKList* h, * t, * p;
    h = NULL;
    for (int i=0;i<n;++i)
    {
        p = (LINKList*)malloc(sizeof(LINKList));
        p->val = a[i];
        p->next = NULL;
        if (!h)
            h = t = p;
        else
        {
            t->next = p;
            t = t->next;
        }
    }
    return h;
}

LINKList* InsertBack(LINKList* h, int data)
{
    LINKList* a=h;
    while (a->next)
        a = a->next;
    LINKList* p = (LINKList*)malloc(sizeof(LINKList));
    p->val = data;
    p->next = NULL;
    a->next = p;
    return h;
}
LINKList* Deleteback(LINKList* h)
{
    LINKList* tmp=h,* tem;
    while (tmp->next)
    {
        tem = tmp;
        tmp = tmp->next;
    }
    tem->next = NULL;
    return h;
}

void Print(LINKList *h)
{
    LINKList* p = h;
    for (; p; p = p->next)
        printf("%d  ",p->val);
}

int main()
{
    int a[] = { 1,2,3,4,5,6,7,8 };
	LINKList* head = Init(a, 8);
    head=InsertBack(head, 10);
    head = Deleteback(head);
    Print(head);
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
