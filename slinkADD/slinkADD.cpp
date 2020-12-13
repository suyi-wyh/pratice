// slinkADD.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>

typedef struct ListNode
{
	int val;
	struct ListNode* next;
}Slink;

Slink* Init(int a[],int n)
{
	Slink* h, *t, *p;
	h = NULL;
	for (int i = 0; i < n; i++)
	{
		p = (Slink *)malloc(sizeof(Slink));
		p->val = a[i];
		p->next = NULL;
		if (h == NULL)
			h = t = p;
		else
			t = t->next = p;
	}
	return h;
}

void Print(Slink* h)
{
	Slink* newnode;
	for (newnode = h; newnode!=NULL; newnode = newnode->next)
		printf("%d  ",newnode->val);
}


struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {

    struct ListNode* list1 = l1;
    struct ListNode* list2 = l2;
    struct ListNode* newlist = NULL, * t;
    int carrybit = 0;


    while (list1 && list2)
    {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newnode->val = list1->val + list2->val + carrybit;
        newnode->next = NULL;
        if (newlist == NULL)
        {
            newlist = t = newnode;
        }
        else
        {
            t = t->next = newnode;
        }


        if (newnode->val % 10 != newnode->val)
        {
            carrybit = 1;
            newnode->val = newnode->val % 10;
        }
        else
        {
            carrybit = 0;
        }

        list1 = list1->next;
        list2 = list2->next;
    }


    while(list1)
    {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newnode->val = list1->val + carrybit;
        newnode->next = NULL;
        t=t->next = newnode;

        if (newnode->val % 10 != newnode->val)
        {
            carrybit = 1;
            newnode->val = newnode->val % 10;
        }
        else
        {
            carrybit = 0;
        }
        list1 = list1->next;
    }
    while(list2)
    {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newnode->val = list2->val + carrybit;
        newnode->next = NULL;
        t=t->next = newnode;

        if (newnode->val % 10 != newnode->val)
        {
            carrybit = 1;
            newnode->val = newnode->val % 10;
        }
        else
        {
            carrybit = 0;
        }
        list2 = list2->next;
    }
    if (1 == carrybit)
    {
        struct ListNode* newnode = (struct ListNode*)malloc(sizeof(struct ListNode));
        newnode->val = 1;
        newnode->next = nullptr;
        t->next = newnode;
    }
    return newlist;
}
int main()
{
    int a[3] = { 2,4,9};
    int b[4] = { 5,6,4,9};
    Slink* head1, * head2,*head3;
    head1 = Init(a,3);
    head2 = Init(b,4);
    Print(head1);
    printf("\n\n");
    Print(head2);

    head3 = addTwoNumbers(head1, head2);
    printf("\n\n\n");
    Print(head3);
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
