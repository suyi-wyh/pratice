
#include"mybinarytree.h"
typedef struct TreeNode
{
	BTtype _val;
	struct TreeNode* _left;
	struct TreeNode* _right;
}BinaryTreeNode;

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

void InOrder(BinaryTreeNode *root)    //�������
{
	if (root != NULL)
	{
		InOrder(root->_left);
		printf("%d\n",root->_val);
		InOrder(root->_right);
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

void PostOrder(BinaryTreeNode *root)  // �������
{
	if (NULL != root)
	{
		PostOrder(root->_left);
		PostOrder(root->_right);
		printf("%d\n", root->_val);
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


int main()
{
	int a[6] = { 4,3,5,2,1,6 };
	BinaryTreeNode* root = InitTree(a,6);
	InOrder(root);
	TreeDestory(&root);
	InOrder(root);
	return 0;
}