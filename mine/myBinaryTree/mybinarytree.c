#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct BinaryTreeNode
{
	int _val;
	struct BinaryTreeNode* _left;
	struct BinaryTreeNode* _right;
}BinaryTreeNode;

BinaryTreeNode* InitTree(int *a,int nums)  //建树
{
	BinaryTreeNode* root;
	root = NULL;

	for(int i=0;i<nums;++i)
	{

	}
	return root;
}

void Inorder(BinaryTreeNode *root)    //中序遍历
{
	if (root != NULL)
	{
		Inorder(root->_left);
		printf("%d\n",root->_val);
		Inorder(root->_right);
	}
}

void PrevOrder(BinaryTreeNode *root)   // 前序遍历
{
	if (NULL != root)
	{
		printf("%d\n",root->_val);
		PrevOrder(root->_left);
		PrevOrder(root->_right);
	}
}

void PostOrder(BinaryTreeNode *root)  // 后序遍历
{
	if (NULL != root)
	{
		PostOrder(root->_left);
		PostOrder(root->_right);
		printf("%d\n", root->_val);
	}
}

int TreeSize(BinaryTreeNode *root)  //求树大小
{
	if (root == NULL)
		return 0;
	return TreeSize(root->_right)+TreeSize(root->_left)+1;

}

int TreeLeafSize(BinaryTreeNode *root)   //叶子数
{
	if (root == NULL)
		return 0;
	if (root->_left == NULL && root->_right == NULL)
		return 1;
	return TreeLeafSize(root->_left) + TreeLeafSize(root->_right);
}

int main()
{
	return 0;
}