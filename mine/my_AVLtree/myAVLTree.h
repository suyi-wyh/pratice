#pragma once

#include<iostream>


template<class K,class V>
class AVLTreeNode {
public:
	AVLTreeNode<K, V>* _left;
	AVLTreeNode<K, V>* _right;
	AVLTreeNode<K, V>* _parent;   // 指向父亲
	std::pair<K, V> _kv;
	int _bf;  // 平衡因子   右边高度减去左边高度

	AVLTreeNode(const pair<K,V>& kv)
		:_left(nullptr)
		,_right(nullptr)
		,_parent(nullptr)
		,_kv(kv)
		,_bf(0)
	{}
};

template<class K,class V>

class myAVLTree {
	typedef AVLTreeNode<K, V> Node;
private:
	Node* _root = nullptr;
	
	int Height(Node* root) {
		if (root == nullptr)
			return 0;
		return std::max(Height(root->_left), Height(root->_right)) + 1;
	}
	// 右旋
	void RotateR(Node* parent) {
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR != nullptr) {
			subLR->_parent = parent;
		}

		Node* parentparent = parent->_parent;
		subL->_right = parent;
		parent->_parent = subL;

		if (parent == _root) {
			_root = subL;
			_root->_parent = nullptr;
		}
		else {   //  更新的部分是一颗子树， 
			if (parentparent->_left == parent) {
				parentparent->_left = subL;
				
			}
			else {
				parentparent->_right = subL;
			}
			subL->_parent = parentparent;
		}

		subL->_bf = parent->_bf =0;
	}
	// 左旋
	void RotateL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if(subRL != nullptr)
			subRL->_parent = parent;

		subR->_left = parent;
		parent->_parent = subR;
		Node* parentparent = parent->_parent;
		if (parent == _root) {
			subR->_parent = nullptr;
		}
		else {
			if (parentparent->_left == parent) {
				parentparent->_left = subR;
			}
			else {
				parentparent->_right = subR;
			}

			subR->_parent = parentparent;
		}

		subR->_bf = parent->_bf = 0;
	}
	// 右左双旋
	void RotateRL(Node* parent) {
		Node* subR = parent->_right;
		Node* subRL = subR->_left;
		int bf = subRL->_bf;

		RotateR(subR);
		RotateL(parent);

		// 平衡因子调节

		if (bf == 1) { // 说明subrl 是在右树插入
			subRL->_bf = 0;
			subR->_bf = 0;
			parent->_bf = -1;
		}
		else if (bf == -1) {  // 说明subrl是在左树插入
			subRL->_bf = 0;
			subR->_bf = 1;
			parent->_bf = 0;
		}
		else { // bf == 0  说明subrl 是新节点
			subRL->_bf = subR->_bf = parent->_bf = 0;
		}
	}
	//左右双旋
	void RotateLR(Node* parent) {

		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		int bf = subLR->_bf;

		RotateL(subL);
		RotateR(parent);

		// 平衡因子调节
		if (bf == 1) { // 说明sublr 是右树插入
			subLR->_bf = 0;
			parent->_bf = 0;
			subL->_bf = -1;
			
		} 
		else if(bf == -1){ //  说明sublr是左树插入
			subLR->_bf = 0;
			parent->_bf = 1;
			subL->_bf = 0;
		}
		else {//bf == 0  说明sublr是新增节点
			subL->_bf = subLR->_bf = parent->_bf = 0;
		}
	}
public:
	myAVLTree() = default;
	// 这里还没写定义
	myAVLTree(const myAVLTree<K, V>& Tree);  // 拷贝构造
	myAVLTree<K, V>& operator=(const myAVLTree<K, V> Tree);
	virtual ~myAVLTree();

	std::pair<Node*, bool>Insert(const std::pair<K, V> kv) {

		// 查找位置
		if (_root == nullptr) {
			_root = new Node(kv);
			return std::make_pair(_root, true);
		}

		Node* parent = nullptr;
		Node* cur = _root;
		while (cur) {
			if (cur->_kv.first < kv.first) {
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_kv.first > kv.first) {
				parent = cur;
				cur = cur->_left;
			}
			else {
				std::make_pair(cur, false);
			}

		}

		//插入
		cur = new Node(kv);
		if (parent->_kv.first < kv.first) {
			parent->_right = cur;
			cur->_parent = parent;
		}
		else {
			parent->_left = cur;
			cur->_parent = parent;
		}
		Node* ret = cur;
		
		//更新平衡因子
		while (parent != nullptr) {
			if (cur == parent->_right) {
				parent->_bf++;
			}
			else {
				parent->_bf--;
			}

			if (abs(parent->_bf) == 1) {
				cur = parent;
				parent = parent->_parent;
			}
			else if (abs(parent->_bf) == 2) {
				//旋转
				if (parent->_bf == -2) {
					if (cur->_bf == -1) {
						RotateR(parent);
					}
					else {
						// 左右双旋
						// ？？？
						RotateLR(parent);
					}
				}
				else {  // == 2
					if (cur->_bf == 1) {
						RotateL(parent);
					}
					else {
						// 右左双旋
						// ???
						RotateRL(parent);
					}
				}
			}
			else break;
		}

		return std::make_pair(ret, true);
	}

	bool _isBalance(Node* root) {
		if (root == nullptr)
			return true;
		int leftheight =Height(root->_left) ;
		int rightheight = Height(root->_right);

		if (leftheight - rightheight != root->_bf) {
			cout << "平衡因子异常：" << root->_kv.first << endl;

		}
		return abs(leftheight - rightheight) < 2 && 
			_isBalance(root->_left) && 
			_isBalance(root->_right);
	}
	bool  isBalance() {
		return _isBalance(_root);
	} 


	Node* Find(const K& key);
	V& operator[](const K& key);
	bool erase(const K& key); 
};