#include"myqueue.h"


int QueueEmpty(queue* que)
{
	if (!que)
	{
		printf("未构建队列");
		exit(0);
	}
	if (NULL == que->_front&&que->_front == que->_tail)
		return 1;
	else
		return 0;
}

queue* QueueInit()
{
	queue* que = (queue*)malloc(sizeof(queue));
	que->_front = que->_tail = NULL;
	return que;
}

void QueuePush(queue* que, QUEUE_TYPE num)        //入队
{ 
	if (QueueEmpty(que))
	{
		que->_front = (queuenode*)malloc(sizeof(queuenode));
		que->_front->_data = num;
		que->_front->_next = NULL;
		que->_tail = que->_front;
	}
	else
	{
		queuenode* newnode = (queuenode*)malloc(sizeof(queuenode));
		newnode->_data = num;
		newnode->_next = NULL;
		que->_tail->_next = newnode;
		que->_tail=que->_tail->_next;
	}
	
}

void QueuePop(queue* que)     //出队
{
	if (QueueEmpty(que))
		return;

	if (NULL != que->_front && que->_front == que->_tail)
	{
		free(que->_front);
		que->_front = que->_tail = NULL;
	}

	else
		que->_front = que->_front->_next;
}

QUEUE_TYPE QueueFront(queue* que)    //获取队首元素
{
	if (QueueEmpty(que))
		return NULL;
	return que->_front->_data;
}


int QueueNums(queue* que)   //获取队列长度  
{
	int nums = 0;
	queuenode* cur = que->_front;
	while (cur)
	{
		++nums;
		cur = cur->_next;
	}
	return nums;
}

QUEUE_TYPE QueueBack(queue* que)    //获取队尾元素
{
	queuenode* cur = que->_front;
	while (cur->_next)
	{
		cur = cur->_next;
	}
	return cur->_data;
}

void QueueDestory(queue* que)   //销毁队列
{
	if (NULL == que)
		return;
	else
	{
		while (que->_front)
		{
			queuenode* next = que->_front->_next;
			free(que->_front);
			que->_front = next;
		}
		que->_tail = que->_front;
	}
}

int main()
{	
	queue* q = QueueInit();
	QueuePush(q,1);
	QueuePush(q,2);
	printf("%d  \n",QueueFront(q));
	printf("%d  \n",QueueFront(q));
	QueuePop(q);
	printf("%d  \n", QueueFront(q));
	QueuePop(q);
	printf("%d  \n", QueueFront(q));
	QueuePop(q);
	return 0;
}