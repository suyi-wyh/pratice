#include"myqueue.h"




int QueueEmpty(queue* que)
{
	if (NULL == que)
		return 1;
	else
		return 0;
}

void QueueInit(queue* que)
{
	que = (queue*)malloc(sizeof(queue));
	que = NULL;
}

void QueuePush(queue* que, QUEUE_TYPE num)
{
	if (NULL == que->_front)
		que->_front = num;
	else
	{
		queue* newnode = (queue*)malloc(sizeof(queue));
		newnode->_front = num;
		newnode->next = NULL;
		que->next = newnode;
	}
}

void QueuePop(queue* que)
{
	if (!QueueEmpty(que))
		return;
	else
		que = que->next;
}

QUEUE_TYPE QueueFront(queue* que)
{
	return que->_front;
}
int QueueNums(queue* que)
{
	int nums = 0;
	while (que)
	{
		++nums;
		que = que->next;
	}
	return nums;
}
QUEUE_TYPE QueueBack(queue* que)
{
	queue* newnode = que;
	while (newnode->next)
	{
		newnode = newnode->next;
	}
	return newnode->_front;
}

void QueueDestory(queue* que)
{
	if (NULL == que)
		return;
	else
		while (que)
			QueuePop(que);
}

int main()
{

}