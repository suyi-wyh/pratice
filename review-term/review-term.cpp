// review-term.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <stdio.h>
#include<stdlib.h>

#define MAX 10
// 顺序表
typedef struct
{
    int* nums;
    int n;
    int length;
}Seqlist;

void InitSeqlist(Seqlist* L)
{
    L->nums = (int*)malloc(MAX * sizeof(int));
    L->n = 0;
    L->length = MAX;
}

void Insert(Seqlist* L, int data)
{
	if (L->n < L->length)
    {
        L->nums[L->n] = data;
        L->n++;
    }
    else
    {
        printf("顺序表已满");
    }
}

void DeleteDate(Seqlist* L, int n)
{
    for (int i = 0; i < L->n;)
    {
        if (L->nums[i] == n)
        {
            for (int j = i; j < L->n - 1; j++)
            {
                L->nums[j] = L->nums[j + 1];
            }
            n--;
        }
        else
            i++;
    }
}
void Print(Seqlist* L)
{
    for (int i = 0; i < L->n; i++)
        printf("%d\n", L->nums[i]);
}
//顺序表

//链表
typedef struct Node
{
    int date;
    struct Node* next;
}SNelem,ListNode;

SNelem* Init(int a[], int n)
{
    SNelem* head, * tail, * newnode;
    head = NULL;
    for (int i = 0; i < n; i++)
    {
        newnode = (SNelem*)malloc(sizeof(SNelem));
        newnode->date = a[i];
        newnode->next = NULL;
        if (head == NULL)
            head = tail = newnode;
        else
            tail = tail->next = newnode;
    }
    return head;
}

void SNelemPrint(SNelem* h)
{
    for (SNelem* newnode = h; newnode; newnode = newnode->next)
        printf("%d\n",newnode->date);
}

void PostInsert(SNelem* h, int date)  //尾插
{
    SNelem* tmp ,*newnode;
    tmp=h;
    for (; tmp->next; tmp = tmp->next);
    newnode = (SNelem*)malloc(sizeof(SNelem));
    newnode->date = date;
    newnode->next = NULL;
    tmp->next = newnode;
}
int CompareMax(SNelem* h)   // 递归寻找链表最大值
{
    int max;
    if (h->next == NULL)
        return h->date;
    else
    {
        max = CompareMax(h->next);
        if (h->date > max)
            max = h->date;
    }
    return max;
}

SNelem* RetBack(SNelem *h)    //翻转链表
{
    SNelem* p, * t;
    p = NULL;
    t = h;
    while(t)
    {
        SNelem *newnode = t->next;
        t->next = p;
        p = t;
        t = newnode;
    }
    return p;
}


bool CheckHuiwen(SNelem* h)  //判断链表的回文结构
{
    SNelem* fast, * slow;
    fast = slow = h;
    while (fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }

    SNelem* t, * p;
    p = NULL;
    t = slow;
    while (t)
    {
        SNelem* newnode = t->next;
        t->next = p;
        p = t;
        t = newnode;
    }

    SNelem* tmp = h;
    while (tmp != slow)
    {
        if (tmp->date == p->date)
        {
            tmp = tmp->next;
            p = p->next;
        }
        else
            break;
    }
    if (tmp == slow)
        return true;
    else
        return false;
}

ListNode* partition(ListNode* pHead, int x) {
    // write code here
    ListNode* small, * psmall;
    ListNode* big, * pbig;
    ListNode* cur = pHead;
    psmall = small = pbig = big = NULL;
    while (cur)
    {
        if (cur->date < x)
        {
            if (small == NULL)
                small = psmall = cur;
            else
            {
                psmall = psmall->next = cur;
            }
        }
        else
        {
            if (big == NULL)
                big = pbig = cur;
            else
            {
                pbig = pbig->next = cur;
            }
        }
        cur = cur->next;
    }

    pbig->next = NULL;
    psmall->next = big;

    return small;

}

SNelem *NPrint(SNelem *h,int k)  //输出链表倒数第k个节点
{
    SNelem* slow, * fast;
    slow = fast = h;
    for (int i = 1; i < k; i++)
    {
        if (fast == NULL)
            return NULL;
        fast = fast->next;
    }
    while (fast->next!=NULL)
    {
        slow = slow->next;
        fast = fast->next;
    }
    return slow;
}

//栈
typedef struct stack
{
    int top;
    int* date;
    int maxsize;
}stack;

int ForgJump(int n)   //青蛙跳台阶
{
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    if (n == 2)
        return 2;
    else
        return ForgJump(n - 1) + ForgJump(n - 2);
}


int Feibonanci(int n)    //斐波那契数列
// 0   1  1  2   3   5   8    13

{
    //用来存放前100项斐波那契数列
    if (n == 1)
        return 0;
    if (n == 2)
        return 1;
    else
        return Feibonanci(n - 1) + Feibonanci(n - 2);
}

int  Feibonanci_t(int n)   //斐波那契数列非递归

//   1    1   2  3  5  8  13
{
	int front, rear,nums;
	nums = front = rear = 1;
    for (; n > 2; n--)
    {
        nums = front + rear;
        front = rear;
        rear = nums;
    }
    return nums;
}


int  ChkBrackets(char *str)             // 花括号匹配
{
    int top = -1;
    char* stack = (char *)malloc(10 *sizeof(char));
    while (*str != '\0')
    {
        if (*str == '(')
        {
            ++top;
            *(stack + top) = *str;
        }
        else if (*str == ')')
        {
            if (top == -1)
                return -1;
            else
                --top;
        }
        *(str++);
    }
    if (top == -1)
        return 1;
    else if (top >= 0)
        return -1;
}
//
int main()
{
   /* Seqlist L;
    InitSeqlist(&L);
    Insert(&L,8);
    Insert(&L,3);
    Insert(&L,2);
    Insert(&L,5);
    Insert(&L,7);
    Print(&L);
    printf("\n\n\n\n\n");*/

    int a[8] = {8,7,6,5,4,3,2,1};
    SNelem* head;
    head = Init(a,8);
    /*if (CheckHuiwen(head))
        printf("YES");
    else
        printf("NO");
    printf("\n\n\n");
    printf("最大值是%d\n",CompareMax(head));*/
    SNelemPrint(head);
    printf("倒数第三个是：%d\n", NPrint(head, 3)->date);
    printf("第五项%d\n", Feibonanci(8));
    printf("第五项%d\n", Feibonanci_t(8));

    char str[] = "(((111))))";
    printf("%d\n", ChkBrackets(str));
    /*SNelemPrint(head);
    head = RetBack(head);
    SNelemPrint(head);*/
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
