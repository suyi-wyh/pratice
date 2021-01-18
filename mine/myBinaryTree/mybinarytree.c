
#include"mybinarytree.h"
typedef struct TreeNode
{
	int _val;
	struct TreeNode* _left;
	struct TreeNode* _right;
}BinaryTreeNode;

BinaryTreeNode* InitTree(int *a,int nums)  //����
{
	BinaryTreeNode* root;
	root = NULL;

	for(int i=0;i<nums;++i)
	{

	}
	return root;
}

void Inorder(BinaryTreeNode *root)    //�������
{
	if (root != NULL)
	{
		Inorder(root->_left);
		printf("%d\n",root->_val);
		Inorder(root->_right);
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
int main()
{
	return 0;
}