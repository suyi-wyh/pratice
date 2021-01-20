#include"myqueue.h"


int QueueEmpty(queue* que)
{
	if (NULL == que->_front)
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

void QueuePush(queue* que, QUEUE_TYPE num)        //���
{ 
	if (que->_front == NULL)
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

void QueuePop(queue* que)     //����
{
	if (NULL == que->_front && que->_front == que->_tail)
		return;

	if (NULL != que->_front && que->_front == que->_tail)
	{
		free(que->_front);
		que->_front = que->_tail = NULL;
	}

	else
		que->_front = que->_front->_next;
}

queuenode* QueueFront(queue* que)    //��ȡ����Ԫ��
{
	return que->_front;
}


int QueueNums(queue* que)   //��ȡ���г���  
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


queuenode* QueueBack(queue* que)    //��ȡ��βԪ��
{
	queuenode* cur = que->_front;
	while (cur->_next)
	{
		cur = cur->_next;
	}
	return cur;
}

void QueueDestory(queue* que)   //���ٶ���
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
	printf("%d  \n",QueueFront(q)->_data);
	printf("%d  \n",QueueFront(q)->_data);
	QueuePop(q);
	printf("%d  \n", QueueFront(q)->_data);
	QueuePop(q);
	printf("%d  \n", QueueFront(q)->_data);
	QueuePop(q);
	return 0;
}