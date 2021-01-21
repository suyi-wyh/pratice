
#include"mybinarytree.h"


BinaryTreeNode* InitTree(BTtype *a,int nums)  //����
{
	BinaryTreeNode* root;
	root = NULL;
	BinaryTreeNode* cur,*prev;
	for (int i = 0; i < nums; ++i)
	{
		BinaryTreeNode* newnode = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
		newnode->_val = a[i];
		newnode->_left = NULL;
		newnode->_right = NULL;
		if (NULL == root)
		{
			root = cur = newnode;
		}
		else
		{
			
			while (TRUE)
			{
				if (cur != NULL)
				{
					prev = cur;
					if (newnode->_val < cur->_val)
					{
						cur = cur->_left;
					}
					else if (newnode->_val > cur->_val)
					{
						
						cur = cur->_right;
					}
				}
				else
				{
					if (prev->_val > newnode->_val)
						prev->_left = newnode;
					else
						prev->_right = newnode;
					break;
				}
			}
			cur = root;
		}
	}
	return root;
}

BinaryTreeNode* CreatTree(char* str, int* num)   //�ַ�����
{
	if ('#' == str[*num])    // '#'����null
	{
		*num += 1;
		return NULL;
	}
	else
	{
		BinaryTreeNode* root = (BinaryTreeNode*)malloc(sizeof(BinaryTreeNode));
		root->_val = str[*num];
		root->_left = NULL;
		root->_right = NULL;
		*num += 1;
		root->_left = CreatTree(str, num);
		root->_right = CreatTree(str, num);
		return root;
	}
}

void InOrder(BinaryTreeNode *root)    //�������
{
	if (root != NULL)
	{
		InOrder(root->_left);
		printf("%d\n",root->_val);
		InOrder(root->_right);
	}
}


void _InOrder(BinaryTreeNode* root)   // �ǵݹ��������
{
	if (!root)
		return;
	BinaryTreeNode** stack = (BinaryTreeNode**)malloc(1000 * sizeof(BinaryTreeNode*));
	int top = 0;
	while (root !=NULL||top>0)
	{
		while (root!=NULL)
		{
			stack[top++] = root;
			root = root->_left;
		}
		root = stack[--top];
		printf("%d \n",root->_val);
		root = root->_right;
	}
}


void PrevOrder(BinaryTreeNode *root)   // ǰ�����
{
	if (NULL != root)
	{
		printf("%d\n",root->_val);
		PrevOrder(root->_left);
		PrevOrder(root->_right);
	}
}

void _PrevOrder(BinaryTreeNode* root)  //����ǰ�����
{
	BinaryTreeNode** stack = (BinaryTreeNode**)malloc(sizeof(BinaryTreeNode*) * 100);
	int top = 0;
	while (root != NULL || top > 0)
	{
		while(root!=NULL){
			printf("%d \n", root->_val);
			stack[top++] = root;
			root = root->_left;

		}
		root = stack[--top];
		root = root->_right;
	}
}



void PostOrder(BinaryTreeNode* root)  // �������
{
	if (NULL != root)
	{
		PostOrder(root->_left);
		PostOrder(root->_right);
		printf("%d\n", root->_val);
	}
}


void _PostOrder(struct TreeNode* root)   //������������
{
	
	if (root == NULL) 
		return;	

	struct TreeNode** stack = (BinaryTreeNode**)malloc(100 * sizeof(struct TreeNode*));
	int top = 0;
	struct TreeNode* prev = NULL;

	while (root != NULL || top > 0) 
	{
		while (root != NULL) 
		{
			stack[top++] = root;
			root = root->_left;
		}

		root = stack[--top];

		if (root->_right == NULL || root->_right == prev) 
		{
			printf("%d \n",root->_val);
			prev = root;
			root = NULL;
		}
		else 
		{
			stack[top++] = root;
			root = root->_right;
		}
	}
}

int BinaryTreeLevelKSize(BinaryTreeNode* root,int k)   //��k��ڵ����
{
	if (!root)
		return 0;
	if (1 == k)
		return 1;
	return BinaryTreeLevelKSize(root->_left, k - 1) + BinaryTreeLevelKSize(root->_right,k-1);
}

void LevelOrder(BinaryTreeNode* root) //�������
{                                    // ���ö��и���ӣ����ӽ��ӣ� ����ʱ��������� ���п�ʱ��������
	if (!root)
		return;
	queue* treeque=QueueInit();
	QueuePush(treeque, root);
	while (!QueueEmpty(treeque))
	{
		BinaryTreeNode* front = QueueFront(treeque);
		printf("%d \n", front->_val);
		QueuePop(treeque);
		if (NULL != front->_left)
			QueuePush(treeque, front->_left);
		if (NULL != front->_right)
			QueuePush(treeque, front->_right);
	}
}


int TreeSize(BinaryTreeNode *root)  //������С
{
	if (root == NULL)
		return 0;
	return TreeSize(root->_right)+TreeSize(root->_left)+1;

}

int TreeLeafSize(BinaryTreeNode *root)   //Ҷ����
{
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}

void TreeDestory(BinaryTreeNode **root)   //������������
{
	if (*root != NULL)
	{
		TreeDestory(&((*root)->_left));
		TreeDestory(&((*root)->_right));
	}
	free(*root);
	*root = NULL;
}

BOOL isUnivalTree(struct TreeNode* root)  // ��ֵ������
{
	if (!root)
		return TRUE;
	int flag = root->_val;
	if (root->_left != NULL && root->_left->_val != flag)
		return FALSE;
	if (root->_right != NULL && root->_right->_val != flag)
		return FALSE;
	return isUnivalTree(root->_left) && isUnivalTree(root->_right);
}

int maxDepth(struct TreeNode* root)   //  ���������
{

	int left, right;
	if (!root)
		return 0;
	left = maxDepth(root->_left);
	right = maxDepth(root->_right);
	return left > right ? left + 1 : right + 1;
}

BOOL isBalanced(struct TreeNode* root)  //�ж�ƽ�������
{
	if (NULL == root)
		return TRUE;
	int flag = abs(maxDepth(root->_left) - maxDepth(root->_right));
	if (flag > 1)
		return FALSE;
	return isBalanced(root->_left) && isBalanced(root->_right);
}

BOOL _isBalanced(BinaryTreeNode* root,int *flag)   //�ж�ƽ�������  O(n)   flag���ڼ�¼�߶�
{
	if (!root)
	{
		*flag = 0;
		return TRUE;
	}
	else
	{
		int leftdepth = 0;
		if(_isBalanced(root->_left, &leftdepth) == FALSE)
			return FALSE;
		int rightdepth = 0;
		if (_isBalanced(root->_right, &rightdepth) == FALSE)
			return FALSE;
		if (abs(leftdepth - rightdepth) > 1)
			return FALSE;
		*flag = leftdepth > rightdepth ? leftdepth + 1 : rightdepth + 1;
		return TRUE;
	}
}


BOOL isSameTree(struct TreeNode* s, struct TreeNode* t)  //�ж����Ƿ���ͬ
{
	if (NULL == s && NULL == t)
		return TRUE;
	return s && t &&
		s->_val == t->_val && 
		isSameTree(s->_left, t->_left) && isSameTree(s->_right, t->_right);
}
BOOL isSubtree(struct TreeNode* s, struct TreeNode* t)    //�ж�t�Ƿ�Ϊs������
{
	if (NULL == s && NULL == t)
		return TRUE;
	if (NULL == s && NULL != t)
		return FALSE;
	return isSameTree(s, t)
		|| isSubtree(s->_left, t)
		|| isSubtree(s->_right, t);
}
struct TreeNode* invertTree(struct TreeNode* root) {  //��ת������

	if (root != NULL)
	{
		struct TreeNode* newnode;
		newnode = root->_left;
		root->_left = root->_right;
		root->_right = newnode;
		invertTree(root->_left);
		invertTree(root->_right);
	}
	return root;
}

BOOL isdef(struct TreeNode* left, struct TreeNode* right)  //�ж������Ƿ��Ǿ���
{
	if (left == NULL && right == NULL)
		return TRUE;
	if (left == NULL || right == NULL)
		return FALSE;
	if (left->_val == right->_val)
		return isdef(left->_left, right->_right) && isdef(left->_right, right->_left);
	return FALSE;
}


BOOL isSymmetric(struct TreeNode* root)   //�ж��Ƿ�������
{
	if (!root)
		return TRUE;
	return isdef(root->_left, root->_right);
}


