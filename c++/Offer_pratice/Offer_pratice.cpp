﻿// Offer_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<StlLock.h>
#include <stack>
#include <list>
#include<StlLock.h>
#include<vector>
#include <unordered_set>
#include<map>
#include<algorithm>
#include<set>
#include<string>
using namespace std;    

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
    
};


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
    
};

/// <summary>
/// 87 扰乱字符串
/// </summary>
class Solution {
private:
	// 记忆化搜索存储状态的数组
	// -1 表示 false，1 表示 true，0 表示未计算
	int memo[30][30][31];
	string s1, s2;

public:
	bool checkIfSimilar(int i1, int i2, int length) {
		unordered_map<int, int> freq;
		for (int i = i1; i < i1 + length; ++i) {
			++freq[s1[i]];
		}
		for (int i = i2; i < i2 + length; ++i) {
			--freq[s2[i]];
		}
		if (any_of(freq.begin(), freq.end(), [](const auto& entry) {return entry.second != 0; })) {
			return false;
		}
		return true;
	}

	// 第一个字符串从 i1 开始，第二个字符串从 i2 开始，子串的长度为 length，是否和谐
	bool dfs(int i1, int i2, int length) {
		if (memo[i1][i2][length]) {
			return memo[i1][i2][length] == 1;
		}

		// 判断两个子串是否相等
		if (s1.substr(i1, length) == s2.substr(i2, length)) {
			memo[i1][i2][length] = 1;
			return true;
		}

		// 判断是否存在字符 c 在两个子串中出现的次数不同
		if (!checkIfSimilar(i1, i2, length)) {
			memo[i1][i2][length] = -1;
			return false;
		}

		// 枚举分割位置
		for (int i = 1; i < length; ++i) {
			// 不交换的情况
			if (dfs(i1, i2, i) && dfs(i1 + i, i2 + i, length - i)) {
				memo[i1][i2][length] = 1;
				return true;
			}
			// 交换的情况
			if (dfs(i1, i2 + length - i, i) && dfs(i1 + i, i2, length - i)) {
				memo[i1][i2][length] = 1;
				return true;
			}
		}

		memo[i1][i2][length] = -1;
		return false;
	}

	bool isScramble(string s1, string s2) {
		memset(memo, 0, sizeof(memo));
		this->s1 = s1;
		this->s2 = s2;
		return dfs(0, 0, s1.size());
	}
};


/// <summary>
/// 173 二叉搜索树迭代器
/// </summary>
class BSTIterator {
private:
    vector<int> ret;
    int nums;

    void inorder(TreeNode* root, vector<int>& arr) {
        if (root) {
            inorder(root->left, arr);
            arr.push_back(root->val);
            inorder(root->right, arr);
        }
    }

    vector<int> TreeNodeinorder(TreeNode* root) {
        vector<int> arr;
        inorder(root, arr);
        return arr;
    }
public:
    BSTIterator(TreeNode* root) :ret(TreeNodeinorder(root)), nums(0)
    {
    }

    int next() {
        return ret[nums++];
    }

    bool hasNext() {
        return nums < ret.size();
    }
};

/// <summary>
/// 208 实现Trie(前缀树)
/// </summary>
class Trie {
private:
	vector<Trie*> tree;
	bool flag;
public:
	/** Initialize your data structure here. */
	Trie() :tree(26), flag(false) {}

	/** Inserts a word into the trie. */
	void insert(string word) {
		Trie* node = this;
		for (auto ch : word) {
			if (node->tree[ch - 'a'] == nullptr)
				node->tree[ch - 'a'] = new Trie();
			node = node->tree[ch - 'a'];
		}
		node->flag = true;
	}

	/** Returns if the word is in the trie. */
	bool search(string word) {
		Trie* node = this;
		for (auto ch : word) {
			if (node->tree[ch - 'a'] == nullptr)
				return false;
			node = node->tree[ch - 'a'];
		}
		return node->flag;
	}

	/** Returns if there is any word in the trie that starts with the given prefix. */
	bool startsWith(string prefix) {
		Trie* node = this;
		for (auto ch : prefix) {
			if (node->tree[ch - 'a'] == nullptr)
				return false;
			node = node->tree[ch - 'a'];
		}
		return true;
	}
};
/// <summary>
/// 705 设计哈希集合
/// </summary>
class MyHashSet {   
private:
    vector<list<int>> data;
    static const int base = 769;
    static int hash(int key) {
        return key % base;
    }
public:
    /** Initialize your data structure here. */
    MyHashSet() :data(base) {

    }

    void add(int key) {
        int flag = hash(key);
        for (auto cur = data[flag].begin(); cur != data[flag].end(); ++cur)
            if (*cur == key)  
                return;    
        data[flag].push_back(key);
    }

    void remove(int key) {
        int flag = hash(key);
        for (auto cur = data[flag].begin(); cur != data[flag].end(); ++cur)
            if (*cur == key) {
                data[flag].erase(cur);
                return;
            }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key) {
        int flag = hash(key);
        for (auto cur = data[flag].begin(); cur != data[flag].end(); ++cur)
            if (*cur == key)
                return true;
        return false;
    }

};

/// <summary>
/// 706 设计哈希映射
/// </summary>
class MyHashMap {
private:
    vector<list<pair<int, int>>> data;
    static const int index = 769;

    static int hash(int key) {
        return key % index;
    }
public:
    /** Initialize your data structure here. */
    MyHashMap() :
        data(index) {
    }

    /** value will always be non-negative. */
    void put(int key, int value) {
        int flag = hash(key);
        for (auto i = data[flag].begin(); i != data[flag].end(); ++i) {
            if ((*i).first == key) {
                (*i).second = value;
                return;
            }
        }
        data[flag].push_back(make_pair(key, value));
    }

    /** Returns the value to which the specified key is mapped, or -1 if this map contains no mapping for the key */
    int get(int key) {
        int flag = hash(key);
        for (auto i = data[flag].begin(); i != data[flag].end(); ++i) {
            if ((*i).first == key)
                return (*i).second;
        }
        return -1;
    }

    /** Removes the mapping of the specified value key if this map contains a mapping for the key */
    void remove(int key) {
        int flag = hash(key);
        for (auto i = data[flag].begin(); i != data[flag].end(); ++i)
            if ((*i).first == key) {
                data[flag].erase(i);
                return;
            }
    }
};


/// <summary>
/// 1603 设计停车系统
/// </summary>
class ParkingSystem {
private:
    int _bigSize;
    int _mediumSize;
    int _smallSize;

    int _bigCapacity;
    int _mediumCapacity;
    int _smallCapacity;
public:

    ParkingSystem(int big, int medium, int small) :
        _bigCapacity(big), _mediumCapacity(medium), _smallCapacity(small)
    {
        _bigSize = _mediumSize = _smallSize = 0;
    }

    bool addCar(int carType) {
        if (carType == 1) {
            if (_bigSize < _bigCapacity) {
                _bigSize++;
                return true;
            }
        }
        else if (carType == 2) {
            if (_mediumSize < _mediumCapacity) {
                _mediumSize++;
                return true;
            }
        }
        else if (carType == 3) {
            if (_smallSize < _smallCapacity) {
                _smallSize++;
                return true;
            }
        }

        return false;
    }
};

class Solution {
public:

    /// <summary>
    /// Offer 10-Ⅱ
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    int numWays(int n) {
        int a = 1;
        int b = 2;
        if (n == 1 || n == 0)
            return 1;
        else if (n == 2)
            return 2;
        int c;
        for (int i = 2; i < n; ++i)
        {
            c = (a + b) % 1000000007;
            a = b;
            b = c;
        }
        return c % 1000000007;
    }
    /// <summary>   
    /// Offer 64
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    int sumNums(int n) {
        int ret = n;
        n && (ret += sumNums(n - 1));
        return ret;
    }

    /// <summary>
    /// 将字符串转换为整数
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    int StrToInt(string str) {
        int ret = 0;
        int n = 0;
        int flag = 1;
        if (str[0] == '-') {
            flag = -1;
            n++;
        }
        else if (str[0] == '+')
            n++;
        else if (str[0] >= '0' && str[0] <= '9');
        else
            return 0;

        while (n < str.size()) {
            if (str[n] >= '0' && str[n] <= '9') {
                ret = ret * 10 + (int)(str[n] - '0');
            }
            else if (str[n] != ' ')
                return 0;
            n++;
        }
        return ret * flag;
    }
    /// <summary>
    /// 3 无重复字符的最长子串
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    int lengthOfLongestSubstring(string s) {
        unordered_set<char> t_hash;
        int  left = 0, right = 0;
        int returnNum = 0;
        while (right < s.size()) {
            while (right < s.length() && !t_hash.count(s[right])) {
                t_hash.insert(s[right]);
                right++;
            }
            returnNum = fmax(right - left, returnNum);
            while (right < s.length() && s[left] != s[right]) {
                t_hash.erase(s[left]);
                left++;
            }
            t_hash.erase(s[left]);
            left++;
        }
        return returnNum;
    }
	/// <summary>
	/// 12 整数转罗马数字
	/// </summary>
	/// <param name="num"></param>
	/// <returns></returns>
	string intToRoman(int num) {
		int tmp = num;
		int flag = 0;
		string ret;
		string nums1 = "IXCM";
		string nums5 = "VLDD";
		while (tmp != 0) {
			int cur = tmp % 10;
			tmp /= 10;
			if (cur == 0);
			else if (cur <= 3) {
				for (int i = 0; i < cur; i++)
					ret.insert(ret.begin(), nums1[flag]);
			}
			else if (cur == 4) {
				ret.insert(ret.begin(), nums5[flag]);
				ret.insert(ret.begin(), nums1[flag]);
			}
			else if (cur == 9) {
				ret.insert(ret.begin(), nums1[flag + 1]);
				ret.insert(ret.begin(), nums1[flag]);
			}
			else {
				for (int i = 0; i < cur - 5; i++) {
					ret.insert(ret.begin(), nums1[flag]);
				}
				ret.insert(ret.begin(), nums5[flag]);
			}
			flag++;
		}
		return ret;
	}
	/// <summary>
	/// 13 罗马数字转整数
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	int romanToInt(string s) {
		map<char, int> nums{ {'I',1},{'V',5},{'X',10},{'L',50},{'C',100},{'D',500},{'M',1000} };
		int n = s.size();
		int i = 0;
		int ret = 0;
		while (i < n - 1) {
			if (nums[s[i]] < nums[s[i + 1]]) {
				ret -= nums[s[i]];
			}
			else
				ret += nums[s[i]];
			i++;
		}
		ret += nums[s[i]];
		return ret;
	}
	/// <summary>
	/// 26 删除有序数组中的重复项
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	int removeDuplicates(vector<int>& nums) {
		int n = nums.size();
		if (n <= 1)
			return n;
		auto it = nums.begin();
		int prev = *it;
		it++;
		while (it != nums.end()) {
			if (*it == prev) {
				it = nums.erase(it);
				n--;
			}
			else {
				prev = *it;
				it++;
			}
		}
		return n;
	}
	
	/// <summary>
	/// 27 移除元素
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="val"></param>
	/// <returns></returns>
	int removeElement(vector<int>& nums, int val) {
		int n = nums.size();
		int right = nums.size() - 1;
		int left = 0;
		while (left <= right)
		{
			if (nums[left] == val) {
				swap(nums[left], nums[right]);
				right--;
				n--;
			}
			else {
				left++;
			}
		}
		return n;
	}  
	
	
	/// <summary>
	/// 19 删除链表的倒数第N个节点
	/// </summary>
	/// <param name="head"></param>
	/// <param name="n"></param>
	/// <returns></returns>
	ListNode* removeNthFromEnd(ListNode* head, int n) {
		ListNode* tmp = new ListNode(0, head);
		head = tmp;
		ListNode* fast = head;
		for (int i = 0; i < n; i++)
			fast = fast->next;
		ListNode* slow = head;
		for (; fast->next != nullptr; fast = fast->next, slow = slow->next);
		ListNode* curd = slow->next;
		slow->next = slow->next->next;
		delete curd;
		return tmp->next;
	}
	/// <summary>
	/// 28 strStr
	/// </summary>
	/// <param name="haystack"></param>
	/// <param name="needle"></param>
	/// <returns></returns>
	int strStr(string haystack, string needle) {
		if (needle == "")
			return 0;

		int i = 0;
		int j = 0;
		while (i + needle.size() - 1 < haystack.size())
		{
			if (haystack[i] == needle[j]) {
				int ii = i;
				int jj = 0;
				while (ii < haystack.size() && jj < needle.size() && haystack[ii] == needle[jj])
				{
					ii++;
					jj++;
					//cout<<"ii:"<<ii<<"jj:"<<jj<<endl;
				}
				if (jj == needle.size())
					return i;
			}
			i++;
		}
		return -1;
	}
	
    /// <summary>
    /// 54 螺旋矩阵
    /// </summary>
    /// <param name="matrix"></param>
    /// <returns></returns>
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        vector<int> returnMatrix;
        int bottom = matrix.size() - 1;
        int right = matrix[0].size() - 1;
        int left = 0, top = 0;
        while (left <= right && top <= bottom) {
            for (int i = left; i <= right; ++i)
                returnMatrix.push_back(matrix[top][i]);
            for (int i = top + 1; i <= bottom; ++i)
                returnMatrix.push_back(matrix[i][right]);
            for (int i = right - 1; i >= left && top < bottom; --i)
                returnMatrix.push_back(matrix[bottom][i]);
            for (int i = bottom - 1; i >= top + 1 && left < right; --i)
                returnMatrix.push_back(matrix[i][left]);
            ++top;
            --bottom;
            right--;
            left++;   
        }
        return returnMatrix;
    }

    /// <summary>
    /// 59  螺旋矩阵Ⅱ
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> returnNum(n, vector<int>(n));
        int left = 0, top = 0;
        int right = n - 1, bottom = n - 1;
        int flag = 1;
        while (left <= right && top <= bottom) {
            for (int i = left; i <= right; ++i)
                returnNum[top][i] = flag++;
            for (int i = top + 1; i <= bottom; ++i)
                returnNum[i][right] = flag++;
            for (int i = right - 1; i >= left && top < bottom; --i)
                returnNum[bottom][i] = flag++;
            for (int i = bottom - 1; i >= top + 1 && left < right; --i)
                returnNum[i][left] = flag++;

            top++;
            bottom--;
            left++;  
            right--;
        }  
        return returnNum;  
    }

    /// <summary>
    /// 61 旋转链表
    /// </summary>
    /// <param name="head"></param>
    /// <param name="k"></param>
    /// <returns></returns>
    ListNode* rotateRight(ListNode* head, int k) {
        ListNode* tmp = head;
        int nums = 1;
        if (!head || !head->next)
            return head;
        while (tmp->next != nullptr) {
            tmp = tmp->next;
            ++nums;
        }
        tmp->next = head;
        int n = nums - k % nums;

        for (int i = 0; i < n; ++i) {
            tmp = tmp->next;
        }
        head = tmp->next;
        tmp->next = nullptr;
        return head;
    }
    /// <summary>
    /// 73 矩阵置零
    /// </summary>
    /// <param name="matrix"></param>
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();

        bool col = false, row = false;

        for (int i = 0; i < n; i++) {
            if (matrix[0][i] == 0)
                col = true;
        }

        for (int i = 0; i < m; ++i) {
            if (matrix[i][0] == 0)
                row = true;
        }

        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j) {
                if (matrix[i][j] == 0) {
                    matrix[0][j] = matrix[i][0] = 0;
                }
            }

        for (int i = 1; i < m; ++i)
            for (int j = 1; j < n; ++j) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0)
                    matrix[i][j] = 0;
            }


        if (col) {
            for (int i = 0; i < n; ++i)
                matrix[0][i] = 0;
        }

        if (row) {
            for (int i = 0; i < m; ++i)
                matrix[i][0] = 0;
        }
    }

    
     
	/// <summary>
	/// 74 搜索二叉树
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	bool searchMatrix(vector<vector<int>>& matrix, int target) {
		int m = matrix.size(), n = matrix[0].size();
		int low = 0, high = m * n - 1;
		while (low <= high) {
			int mid = (high - low) / 2 + low;
			int x = matrix[mid / n][mid % n];
			if (x < target) {
				low = mid + 1;
			}
			else if (x > target) {
				high = mid - 1;
			}
			else {
				return true;
			}
		}
		return false;
	}

    /// <summary>
    /// 80 删除有序数组中的重复项Ⅱ
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    int removeDuplicates(vector<int>& nums) {
        int n = nums.size();
        if (n <= 2) {
            return n;
        }
        int slow = 2, fast = 2;
        while (fast < n) {
            if (nums[slow - 2] != nums[fast]) {
                nums[slow] = nums[fast];
                ++slow;
            }
            ++fast;
        }
        return slow;
    }
	
	
	///搜索旋转排序数组Ⅱ
    bool search(vector<int> &nums, int target) {
        int n = nums.size();
        if (n == 0) {
            return false;
        }
        if (n == 1) {
            return nums[0] == target;
        }
        int l = 0, r = n - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (nums[mid] == target) {
                return true;
            }
            if (nums[l] == nums[mid] && nums[mid] == nums[r]) {
                ++l;
                --r;
            } else if (nums[l] <= nums[mid]) {
                if (nums[l] <= target && target < nums[mid]) {
                    r = mid - 1;
                } else {
                    l = mid + 1;
                }
            } else {
                if (nums[mid] < target && target <= nums[n - 1]) {
                    l = mid + 1;
                } else {
                    r = mid - 1;
                }
            }
        }
        return false;
    }
    /// <summary>
    /// 82 删除排序链表中的重复元素
    /// </summary>
    /// <param name="head"></param>
    /// <returns></returns>
    ListNode* deleteDuplicates(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        while (head && head->next && head->val == head->next->val) {
            ListNode* p = head->next;
            while (p != nullptr && head->val == p->val)
                p = p->next;
            head = p;
        }

        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode* cur = head;
        ListNode* tmp = head->next;

        while (cur->next && cur->next->next != nullptr) {
            if (tmp->val == tmp->next->val) {
                ListNode* pre = tmp->next;
                while (pre != nullptr && tmp->val == pre->val)
                    pre = pre->next;
                cur->next = pre;
                tmp = cur->next;
            }
            else {
                cur = cur->next;
                tmp = tmp->next;
            }
        }
        return head;

    }


    /// <summary>
    /// 83 删除排序链表中的重复元素
    /// </summary>
    /// <param name="head"></param>
    /// <returns></returns>
    ListNode* deleteDuplicates(ListNode* head) {

        if (head == nullptr || head->next == nullptr)
            return head;

        ListNode* cur = head;
        while (cur->next != nullptr) {
            if (cur->val == cur->next->val)
                cur->next = cur->next->next;
            else
                cur = cur->next;
        }

        return head;
    }


    /// <summary>
    /// 88 合并两个有序数组
    /// </summary>
    /// <param name="nums1"></param>
    /// <param name="m"></param>
    /// <param name="nums2"></param>
    /// <param name="n"></param>
    void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
        int i = m + n - 1;
        m--;
        n--;
        while (m >= 0 && n >= 0) {
            if (nums1[m] >= nums2[n]) {
                nums1[i] = nums1[m];

                i--; m--;
            }
            else {
                nums1[i] = nums2[n];
                i--; n--;
            }
        }
        while (n >= 0) {
            nums1[i] = nums2[n];
            i--; n--;
        }

    }
	
	/// <summary>
	///  91 解码方法
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	int numDecodings(string s) {
		int n = s.size();
		vector<int> f(n + 1);
		f[0] = 1;
		for (int i = 1; i <= n; ++i) {
			if (s[i - 1] != '0') {
				f[i] += f[i - 1];
			}
			if (i > 1 && s[i - 2] != '0' && ((s[i - 2] - '0') * 10 + (s[i - 1] - '0') <= 26)) {
				f[i] += f[i - 2];
			}
		}
		return f[n];
	}
    /// <summary>
    /// 92 反转链表Ⅱ
    /// </summary>
    /// <param name="head"></param>
    /// <param name="left"></param>
    /// <param name="right"></param>
    /// <returns></returns>
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        if (left == right)
            return head;
        int preleft = 1;
        ListNode* pre = head;
        while (preleft < left - 1) {
            pre = pre->next;
            preleft++;
        }

        if (left == 1) {
            ListNode* tmp = new ListNode(0);
            tmp->next = head;
            pre = tmp;
        }

        int i = 0;
        ListNode* curleft = pre->next;
        ListNode* cur = curleft->next;

        while (i < right - left) {
            ListNode* n = cur->next;
            cur->next = pre->next;
            curleft->next = n;
            pre->next = cur;
            cur = curleft->next;
            ++i;
        }

        if (left == 1) {
            head = pre->next;
        }

        return head;
    }
	
	/// <summary>
	/// 94 二叉树的中序遍历
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	vector<int> inorderTraversal(TreeNode* root) {
		vector<int> ret;
		if (!root)
			return ret;
		stack<TreeNode*> stk;

		while (!stk.empty() || root != nullptr) {
			while (root != nullptr) {
				stk.push(root);
				root = root->left;
			}

			ret.push_back(stk.top()->val);
			root = stk.top()->right;
			stk.pop();
		}
		return ret;
	}
	/// <summary>
	/// 105 从前序与中序遍历序列构造二叉树
	/// </summary>
	/// <param name="preorder"></param>
	/// <param name="inorder"></param>
	/// <param name="pi"></param>
	/// <param name="ibegin"></param>
	/// <param name="iend"></param>
	/// <returns></returns>
	TreeNode* PreOrder(vector<int>& preorder, vector<int>& inorder, int& pi, int ibegin, int iend) {

		if (pi >= preorder.size() || ibegin > iend)
			return nullptr;

		int rooti = ibegin;
		while (rooti <= iend && inorder[rooti] != preorder[pi]) {
			rooti++;
		}
		TreeNode* root = new TreeNode(preorder[pi]);
		++pi;

		root->left = PreOrder(preorder, inorder, pi, ibegin, rooti - 1);
		root->right = PreOrder(preorder, inorder, pi, rooti + 1, iend);
		return root;
	}
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
		int pi = 0;
		return PreOrder(preorder, inorder, pi, 0, inorder.size() - 1);
	}
    /// <summary>
    /// 115 不同的子序列
    /// </summary>
    /// <param name="s"></param>
    /// <param name="t"></param>
    /// <returns></returns>
    int numDistinct(string s, string t) {
        int n = s.length();
        int m = t.length();
        if (n < m)
            return 0;
        long cur = 0;
        long nums[m][n];
        memset(nums, 0, sizeof(nums));

        for (int i = n - 1; i >= 0; i--) {
            if (s[i] == t[m - 1])
                nums[m - 1][i] = 1.0;
        }

        for (int i = m - 2; i >= 0; i--)
        {
            int cur = n - 1;
            int ans = 0;
            while (s[cur] != t[i]) {
                ans += nums[i + 1][cur];
                cur--;
            }
            for (int j = cur; j >= 0; --j) {
                if (s[j] == t[i]) {
                    nums[i][j] = ans;
                }
                ans += nums[i + 1][j];
            }
        }
        int sum = 0;

        for (int i = 0; i < n; ++i) {
            sum += nums[0][i];
        }
        return sum;
    }
    /// <summary>
    /// 118 杨辉三角
    /// </summary>
    /// <param name="numRows"></param>
    /// <returns></returns>
    vector<vector<int>> generate(int numRows) {
        vector<vector<int>> ret;
        ret.resize(numRows, vector<int>());
        ret[0].push_back(1);
        for (int i = 1; i < numRows; ++i) {
            ret[i].resize(i + 1, 0);
            ret[i][0] = 1;
            ret[i][i] = 1;
            for (int j = 1; j < i; ++j) {
                ret[i][j] = ret[i - 1][j - 1] + ret[i - 1][j];
            }
        }
        return ret;
    }

    /// <summary>
    /// 137 只出现一次的数字
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    int singleNumber(vector<int>& nums) {
        set<int> num;
        long num1 = 0;
        for (int i = 0; i < nums.size(); ++i) {
            num.insert(nums[i]);
            num1 += nums[i];
        }

        long num2 = 0;
        for (auto it = num.begin(); it != num.end(); ++it)
            num2 += *it;
        num2 *= 3;
        return (num2 - num1) / 2;
    }
	
	/// <summary>
	/// 145 二叉树的后序遍历
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> ret;
		if (!root)
			return ret;
		stack<TreeNode*> stk;

		TreeNode* pre = nullptr;
		while (!stk.empty() || root != nullptr) {

			while (root != nullptr) {
				stk.push(root);
				root = root->left;
			}

			root = stk.top();
			stk.pop();

			if (root->right == nullptr || root->right == pre) {
				ret.push_back(root->val);
				pre = root;
				root = nullptr;
			}
			else {
				stk.push(root);
				root = root->right;
			}
		}
		return ret;
	}
    /// <summary>
    /// 150 逆波兰表达式求值
    /// </summary>
    /// <param name="str"></param>
    /// <returns></returns>
    bool isNumbers(string str) {
        return !(str == "+" || str == "-" || str == "/" || str == "*");
    }


    int evalRPN(vector<string>& tokens) {
        stack<int> stk;
        for (auto ch : tokens) {
            if (isNumbers(ch))
                stk.push(atoi(ch.c_str()));
            else {
                int x = stk.top();
                stk.pop();
                int y = stk.top();
                stk.pop();
                if (ch == "+")
                    stk.push(x + y);
                else if (ch == "-")
                    stk.push(y - x);
                else if (ch == "*")
                    stk.push(x * y);
                else if (ch == "/")
                    stk.push(y / x);
            }

        }

        return stk.top();
    }

    /// <summary>
    /// 153 寻找旋转排序数组中的最小值
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    int findMin(vector<int>& nums) {
        int right = 0;
        int left = nums.size() - 1;
        while (right < left) {
            int mid = (right + left) / 2;
            if (nums[mid] < nums[left]) {
                left = mid;
            }
            else {
                right = mid + 1;
            }
        }
        return nums[right];
    }

    /// <summary>
    /// 154 寻找旋转排序数组中的最小值Ⅱ
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    int findMin(vector<int>& nums) {
        int right = nums.size();
        if (right == 1)
            return nums[0];
        int left = 0;
        right--;
        while (left < right) {
            int mid = (left + right) / 2;

            if (nums[mid] > nums[right])
                left = mid + 1;
            else if (nums[mid] == nums[right])
                right--;
            else {
                right = mid;
            }
        }
        return nums[right];
    }

    /// <summary>
    /// 179 最大数
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    string largestNumber(vector<int>& nums) {
        string ret;
        sort(nums.begin(), nums.end(), [](const int& x, const int& y) {
            long _x = 10, _y = 10;
            while (_x <= x)
                _x *= 10;
            while (_y <= y)
                _y *= 10;

            return x * _y + y > y * _x + x;
            });
        if (nums[0] == 0)
            return "0";
        for (const auto ch : nums) {
            ret += to_string(ch);
        }
    /// <summary>
    /// 190 颠倒二进制位
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    uint32_t reverseBits(uint32_t n) {
        uint32_t ret = 0;
        for (int i = 0; i < 32; i++) {
            ret = ret * 2 + n % 2;
            n /= 2;
        }
        return ret;
    }
	
	
	/// <summary>
	/// 213 打家劫舍Ⅱ
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="start"></param>
	/// <param name="end"></param>
	/// <returns></returns>
	int dfs(vector<int>& nums, int start, int end) {
		int first = nums[start], second = max(nums[start], nums[start + 1]);
		for (int i = start + 2; i < end; i++) {
			int tmp = second;
			second = max(second, first + nums[i]);
			first = tmp;
		}

		return second;
	}
	int rob(vector<int>& nums) {
		if (nums.size() == 1)
			return nums[0];
		else if (nums.size() == 2)
			return max(nums[0], nums[1]);

		return max(dfs(nums, 0, nums.size() - 1), dfs(nums, 1, nums.size()));
	}
	/// <summary>
	/// 244 二叉树的前序遍历
	/// </summary>
	/// <param name="root"></param>
	/// <returns></returns>
	vector<int> preorderTraversal(TreeNode* root) {
		vector<int> ret;
		if (root == nullptr)
			return ret;
		stack<TreeNode*> stk;

		while (!stk.empty() || root != nullptr) {
			while (root != nullptr) {
				ret.push_back(root->val);
				stk.push(root);
				root = root->left;
			}
			root = stk.top();
			stk.pop();
			root = root->right;
		}
		return ret;
	}  
    /// <summary>
    /// 224 基础计算器
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    int calculate(string s) {
        stack<int> stk;
        stk.push(1);
        int sum = 0;
        int flag = 1;
        for (int i = 0; i < s.length();)
        {
            if (s[i] >= '0' && s[i] <= '9')
            {
                long int relit = 0;
                while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                    relit = relit * 10 + s[i] - '0';
                    i++;
                }
                sum += (flag * relit);

            }
            else
            {
                if (s[i] == '(')
                    stk.push(flag);
                else if (s[i] == ')')
                    stk.pop();
                else if (s[i] == '+')
                    flag = stk.top();
                else if (s[i] == '-')
                {
                    flag = -stk.top();
                }
                ++i;
            }
        }
        return sum;
    }

    /// <summary>
    /// 191 位1的个数
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    int hammingWeight(uint32_t n) {
        int ret = 0;
        while (n) {
            n &= n - 1;
            ret++;

        }
        return ret;
    }


    /// <summary>
    /// 227 基本计算器
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    int calculate(string s) {
        stack<int> stk;
        int num = 0;
        char flag = '+';

        for (int i = 0; i < s.length();) {
            if (s[i] == ' ')
                ++i;

            if (s[i] >= '0' && s[i] <= '9') {
                num = 0;
                while (i < s.length() && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + (s[i] - '0');
                    ++i;
                }
            }

            if (i >= s.length() - 1 || (!(s[i] >= '0' && s[i] <= '9') && s[i] != ' '))
            {
                if (flag == '+')
                    stk.push(num);
                else if (flag == '-') 
                    stk.push(0 - num);
                else if (flag == '*') {
                    flag = '*';
                    num = stk.top() * num;
                    stk.pop();
                    stk.push(num);
                }
                else if (flag == '/') {
                    flag = '/';
                    num = stk.top() / num;
                    stk.pop();
                    stk.push(num);
                }
                flag = s[i];
                i++;
                num = 0;
            }
        }
        int ret = 0;
        while (!stk.empty()) {
            ret += stk.top();
            stk.pop();
        }
        return ret;
    }
	
	/// <summary>
	/// 236 二叉树的最近公共祖先
	/// </summary>
	/// <param name="root"></param>
	/// <param name="p"></param>
	/// <param name="q"></param>
	/// <returns></returns>
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
		stack<TreeNode*> stkp;
		stack<TreeNode*> stkq;

		findpath(root, p, stkp);
		findpath(root, q, stkq);

		int np = stkp.size();
		int nq = stkq.size();

		if (np > nq) {
			for (int i = 0; i < np - nq; ++i)
				stkp.pop();
		}
		else if (nq > np) {
			for (int i = 0; i < nq - np; ++i)
				stkq.pop();
		}

		while (stkp.top() != stkq.top()) {
			stkp.pop();
			stkq.pop();
		}

		return stkq.top();
	}
    /// <summary>
    /// 263 丑数
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    bool isUgly(int n) {
        if (n == 1)
            return true;
        else if (n < 1)
            return false;
        while (n % 5 == 0)
            n /= 5;
        while (n % 3 == 0)
            n /= 3;
        while (n % 2 == 0)
            n /= 2;
        return n == 1;
    }



    /// <summary>
    /// 264 丑数Ⅱ
    /// </summary>
    /// <param name="n"></param>
    /// <returns></returns>
    int nthUglyNumber(int n) {    
        vector<int> dp(n + 1);
        dp[1] = 1;
        int dp2 = 1, dp3 = 1, dp5 = 1;
        for (int i = 2; i <= n; i++) {
            dp[i] = min(min(2 * dp[dp2], 3 * dp[dp3]), 5 * dp[dp5]);
            cout << i << ':' << dp[i] << endl;
            if (dp[i] == 2 * dp[dp2])
                dp2++;
            if (dp[i] == 3 * dp[dp3])
                dp3++;
            if (dp[i] == 5 * dp[dp5])
                dp5++;
        }

        return dp[n];
    }
    /// <summary>
    /// 331 验证二叉树的前序序列化
    /// </summary>
    /// <param name="preorder"></param>
    /// <returns></returns>
    bool isValidSerialization(string preorder) {
        int x = 0;
        int i = 0;
        int n = preorder.length();
        if (preorder[i] == '#' && n == 1)
            return true;
        else if (preorder[i] == '#')
            return false;
        while (i < n - 1) {
            if (preorder[i] == '#') {
                if (x == 0)
                    return false;
                else
                    x--;
                ++i;
            }
            else
            {
                int num = 0;
                while (i < n && preorder[i] != ',') {
                    num = num * 10 + preorder[i] - '0';
                    ++i;
                }
                x++;
            }
            ++i;
        }
        return x == 0 && preorder[n - 1] == '#';
    }


    /// <summary>
    /// 344 反转字符串
    /// </summary>
    /// <param name="s"></param>
    void reverseString(vector<char>& s) {
        int i = 0;
        int n = s.size() - 1;

        while (i < n) {
            swap(s[i],s[n]);
            i++; n--;
        }
    }

	/// <summary>
	/// 363 矩形区域不超过K的最大数
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	int maxSumSubmatrix(vector<vector<int>>& matrix, int k) {
		int ans = INT_MIN;
		int m = matrix.size(), n = matrix[0].size();
		for (int i = 0; i < m; ++i) { // 枚举上边界
			vector<int> sum(n);
			for (int j = i; j < m; ++j) { // 枚举下边界
				for (int c = 0; c < n; ++c) {
					sum[c] += matrix[j][c]; // 更新每列的元素和
				}
				set<int> sumSet{ 0 };
				int s = 0;
				for (int v : sum) {
					s += v;
					auto lb = sumSet.lower_bound(s - k);
					if (lb != sumSet.end()) {
						ans = max(ans, s - *lb);
					}
					sumSet.insert(s);
				}
			}
		}
		return ans;
	}

	/// <summary>
	/// 368 最大整除子集
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	vector<int> largestDivisibleSubset(vector<int>& nums) {
		int len = nums.size();
		sort(nums.begin(), nums.end());

		vector<int> dp(len, 1);
		int maxSize = 1;
		int maxVal = dp[0];
		for (int i = 1; i < len; i++) {
			for (int j = 0; j < i; j++) {
				if (nums[i] % nums[j] == 0) {
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}

			if (dp[i] > maxSize) {
				maxSize = dp[i];
				maxVal = nums[i];
			}
		}


		vector<int> res;
		if (maxSize == 1) {
			res.push_back(nums[0]);
			return res;
		}

		for (int i = len - 1; i >= 0 && maxSize > 0; i--) {
			if (dp[i] == maxSize && maxVal % nums[i] == 0) {
				res.push_back(nums[i]);
				maxVal = nums[i];
				maxSize--;
			}
		}
		return res;
	}
	
	/// <summary>
	/// 377 组合总和Ⅳ
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	int combinationSum4(vector<int>& nums, int target) {
		vector<int> dp(target + 1);
		dp[0] = 1;
		for (int i = 1; i <= target; i++) {
			for (int& num : nums) {
				if (num <= i && dp[i - num] < INT_MAX - dp[i]) {
					dp[i] += dp[i - num];
				}
			}
		}
		return dp[target];
	}
    /// <summary>
    /// 387 字符串中的唯一字符
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    int firstUniqChar(string s) {
        int Size[26] = { 0 };
        for (auto ch : s)
        {
            Size[ch - 'a']++;
        }
        for (size_t i = 0; i < s.size(); ++i)
            if (Size[s[i] - 'a'] == 1)
                return i;
        return -1;
    }

    /// <summary>
    /// 456 132模式
    /// </summary>
    /// <param name="nums"></param>
    /// <returns></returns>
    bool find132pattern(vector<int>& nums) {
        int n = nums.size();
            stack<int> stk;
        stk.push(nums[n - 1]);
        int max_2 = INT_MIN;

        for (int i = n - 2; i >= 0; i--) {
            if (nums[i] < max_2)
                return true;

            while (!stk.empty() && nums[i] > stk.top()) {
                max_2 = stk.top();
                stk.pop();
            }

            if (nums[i] > max_2)
                stk.push(nums[i]);
        }
        return true;
    }

	/// <summary>
	/// 403 青蛙过河
	/// </summary>
	/// <param name="stones"></param>
	/// <returns></returns>
	bool canCross(vector<int>& stones) {
		int n = stones.size();
		vector<vector<int>> dp(n, vector<int>(n));
		dp[0][0] = true;
		for (int i = 1; i < n; ++i) {
			if (stones[i] - stones[i - 1] > i) {
				return false;
			}
		}
		for (int i = 1; i < n; ++i) {
			for (int j = i - 1; j >= 0; --j) {
				int k = stones[i] - stones[j];
				if (k > j + 1) {
					break;
				}
				dp[i][k] = dp[j][k - 1] || dp[j][k] || dp[j][k + 1];
				if (i == n - 1 && dp[i][k]) {
					return true;
				}
			}
		}
		return false;
	}
    /// <summary>
    /// 541 反转字符串Ⅱ
    /// </summary>
    /// <param name="s"></param>
    /// <param name="k"></param>
    /// <returns></returns>
    string reverseStr(string s, int k) {
        for (int start = 0; start < s.size(); start += 2 * k) {
            int i = start;
            int j = fmin(start + k - 1, s.size() - 1);
            while (i < j) {
                char tmp = s[i];
                s[i++] = s[j];
                s[j--] = tmp;
            }
        }
        return s;
    }


    /// <summary>
    /// 557 反转字符串中的单词Ⅲ
    /// </summary>
    /// <param name="s"></param>
    /// <returns></returns>
    string reverseWords(string s) {
        for (int start = 0; start < s.size();) {
            int i = start;
            int j = start;
            for (; s[j] != ' ' && j < s.size(); j++);
            start = j + 1;
            j--;
            cout << "i" << i << endl;
            cout << "j" << j << endl;
            cout << "star:" << start << endl;
            while (i < j) {
                swap(s[i], s[j]);
                i++;
                j--;
            }
        }
        return s;
    }
	
	/// <summary>
	/// 633 平方数之和
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	bool judgeSquareSum(int c) {
		int gc = sqrt(c);
		for (int i = 0; i <= gc; i++) {
			int tmp = c - pow(i, 2);
			int ttmp = sqrt(tmp);
			if (ttmp * ttmp == tmp)
				return true;
		}
		return false;
	}
	/// <summary>
	/// 740 删除并获得点数
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	int rob(vector<int>& nums) {
		int size = nums.size();
		int first = nums[0], second = max(nums[0], nums[1]);
		for (int i = 2; i < size; i++) {
			int temp = second;
			second = max(first + nums[i], second);
			first = temp;
		}
		return second;
	}
	int deleteAndEarn(vector<int>& nums) {
		int maxVal = 0;
		for (int val : nums) {
			maxVal = max(maxVal, val);
		}
		vector<int> sum(maxVal + 1);
		for (int val : nums) {
			sum[val] += val;
		}
		return rob(sum);
	}
    /// <summary>
    /// 781 森林中的兔子
    /// </summary>
    /// <param name="answers"></param>
    /// <returns></returns>
    int numRabbits(vector<int>& answers) {
        vector<int> flag(1000, 0);
        int n = answers.size();
        int ret = 0;
        for (int i = 0; i < n; ++i) {
            if (answers[i] == 0) {
                ret++;
            }
            else if (flag[answers[i]] == 0) {
                ++flag[answers[i]];
                ret += answers[i] + 1;
            }
            else if (flag[answers[i]] == answers[i]) {
                flag[answers[i]] = 0;
            }
            else
                flag[answers[i]]++;
        }
        return ret;
    }
	
	/// <summary>
	/// 783 二叉搜索树节点最小距离
	/// </summary>
	/// <param name="ret"></param>
	/// <param name="val"></param>
	/// <param name="root"></param>
	void InOrder(int& ret, int& val, TreeNode* root) {
		if (!root)
			return;

		InOrder(ret, val, root->left);
		if (val == INT_MAX)
			val = root->val;
		else {
			ret = min(ret, abs(val - root->val));
			val = root->val;
		}
		InOrder(ret, val, root->right);
	}

	int minDiffInBST(TreeNode* root) {
		int ret = INT_MAX;
		int val = INT_MAX;
		InOrder(ret, val, root);
		return ret;
	}
	
	/// <summary>
	/// 872 叶子相似的树
	/// </summary>
	/// <param name="root"></param>
	/// <param name="nums"></param>
	void _InOrder(TreeNode* root, vector<int>& nums) {
		if (root != nullptr) {
			InOrder(root->left, nums);
			if (root->left == nullptr && root->right == nullptr)
				nums.push_back(root->val);
			InOrder(root->right, nums);
		}
	}
	bool leafSimilar(TreeNode* root1, TreeNode* root2) {
		vector<int> nums1;
		vector<int> nums2;

		_InOrder(root1, nums1);
		_InOrder(root2, nums2);

		return nums1 == nums2;

	}
	/// <summary>
	/// 897 递增顺序搜索树
	/// </summary>
	/// <param name="root"></param>
	/// <param name="nums"></param>
	void InOrder(TreeNode* root, vector<int>& nums) {
		if (root != nullptr) {
			InOrder(root->left, nums);
			nums.push_back(root->val);
			InOrder(root->right, nums);
		}
	}
	TreeNode* increasingBST(TreeNode* root) {
		if (!root)
			return nullptr;

		vector<int> nums;
		InOrder(root, nums);

		TreeNode* newroot = new TreeNode(nums[0]);
		TreeNode* pre = newroot;
		for (int i = 1; i < nums.size(); i++) {
			TreeNode* tmp = new TreeNode(nums[i]);
			pre = pre->right = tmp;
		}

		return newroot;
	}
    /// <summary>
    /// 917 仅仅翻转字母
    /// </summary>
    /// <param name="S"></param>
    /// <returns></returns>
    string reverseOnlyLetters(string S) {
        int begin = 0;
        int end = S.size() - 1;
        while (begin < end)
        {
            while (begin < end && !((S[begin] >= 'a' && S[begin] <= 'z') || (S[begin] >= 'A' && S[begin] <= 'Z')))
                begin++;
            while (begin < end && !((S[end] >= 'a' && S[end] <= 'z') || (S[end] >= 'A' && S[end] <= 'Z')))
                end--;
            swap(S[begin], S[end]);
            begin++;
            end--;
        }
        return S;
    }

	/// <summary>
	/// 938 二叉搜索树的范围和
	/// </summary>
	/// <param name="root"></param>
	/// <param name="low"></param>
	/// <param name="high"></param>
	/// <param name="sum"></param>
	void Inorder(TreeNode* root, int low, int high, int& sum) {
		if (root) {
			Inorder(root->left, low, high, sum);
			if (root->val <= high && root->val >= low) {
				//cout<<"jinlaile"<<endl;
				sum += root->val;
			}
			Inorder(root->right, low, high, sum);
		}
	}
	int rangeSumBST(TreeNode* root, int low, int high) {
		int sum = 0;
		Inorder(root, low, high, sum);
		return sum;
	}
	/// <summary>
	/// 993 二叉树的堂兄弟节点
	/// </summary>
	/// <param name="root"></param>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	bool isCousins(TreeNode* root, int x, int y) {
		if (!root || !root->left || !root->right)
			return false;
		vector<TreeNode*> curV;
		vector<TreeNode*> nextV;

		curV.push_back(root);
		while (!curV.empty() || !nextV.empty()) {
			bool flagx = false;
			bool flagy = false;

			for (int i = 0; i < curV.size(); ++i) {
				if (!curV[i]->left && !curV[i]->right);
				else if (!curV[i]->left && curV[i]->right) {
					nextV.push_back(curV[i]->right);
					if (curV[i]->right->val == x)
						flagx = true;
					else if (curV[i]->right->val == y)
						flagy = true;
				}

				else if (curV[i]->left && !curV[i]->right) {
					nextV.push_back(curV[i]->left);
					if (curV[i]->left->val == x)
						flagx = true;
					else if (curV[i]->left->val == y)
						flagy = true;
				}

				else {
					if (curV[i]->left->val == x && curV[i]->right->val == y)
						return false;
					else if (curV[i]->left->val == y && curV[i]->right->val == x)
						return false;

					if (curV[i]->left->val == x)
						flagx = true;
					else if (curV[i]->left->val == y)
						flagy = true;
					if (curV[i]->right->val == x)
						flagx = true;
					else if (curV[i]->right->val == y)
						flagy = true;
					nextV.push_back(curV[i]->left);
					nextV.push_back(curV[i]->right);
				}
			}
			if (flagx && flagy) {
				return true;
			}
			curV.clear();
			swap(curV, nextV);
		}
		return false;
	}
    /// <summary>
    /// 1006 笨阶乘
    /// </summary>
    /// <param name="N"></param>
    /// <returns></returns>
    int clumsy(int N) {
        stack<int> stk;
        stk.push(N);
        N--;
        for (int i = 0; N > 0; i++) {
            if (i % 4 == 0) {
                int x = stk.top();
                stk.pop();
                stk.push(x * N);
            }
            else if (i % 4 == 1) {
                int x = stk.top();
                stk.pop();
                stk.push(x / N);
            }
            else if (i % 4 == 2) {
                stk.push(N);
            }
            else
                stk.push(-N);
            N--;
        }

        int ret = 0;
        while (!stk.empty()) {
            ret += stk.top();
            stk.pop();
        }
        return ret;
    }
	/// <summary>
	/// 1011   在D天内送达包裹的能力
	/// </summary>
	/// <param name="weights"></param>
	/// <param name="D"></param>
	/// <returns></returns>
	int shipWithinDays(vector<int>& weights, int D) {
		int left = *max_element(weights.begin(), weights.end());
		int right = accumulate(weights.begin(), weights.end(), 0);
		while (left < right) {  
			int mid = (left + right) / 2;
			int days = 1, weight = 0;
			for (int it : weights) {
				weight += it;
				if (weight > mid) {
					days++;
					weight = it;
				}
			}

			if (days <= D) {
				right = mid;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}
	/// <summary>
	/// 1047 删除字符串中的所有相邻重复项
	/// </summary>
	/// <param name="S"></param>
	/// <returns></returns>
	string removeDuplicates(string S) {
		string stk;
		for (auto ch : S)
		{
			if (!stk.empty() && stk.back() == ch)
				stk.pop_back();
			else
				stk.push_back(ch);
		}
		return stk;
	}
    

    /// <summary>
    /// 1143 最长公共子序列
    /// </summary>
    /// <param name="text1"></param>  
    /// <param name="text2"></param>
    /// <returns></returns>
    int longestCommonSubsequence(string text1, string text2) { 
        int m = text1.size();
        int n = text2.size();
        vector<vector<int>> nums(m + 1, vector<int>(n + 1));
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (text1[i] == text2[j])
                    nums[i + 1][j + 1] = nums[i][j] + 1;
                else
                    nums[i + 1][j + 1] = max(nums[i][j + 1], nums[i + 1][j]);
            }
        }
        return nums[m][n];
    }

	/// <summary>
	/// 1269 停在原地的方案数
	/// </summary>
	/// <param name="steps"></param>
	/// <param name="arrLen"></param>
	/// <returns></returns>
	int numWays(int steps, int arrLen) {  
		const int MODULO = 1000000007;
		int maxColumn = min(arrLen - 1, steps);
		vector<vector<int>> dp(steps + 1, vector<int>(maxColumn + 1));
		dp[0][0] = 1;
		for (int i = 1; i <= steps; i++) {
			for (int j = 0; j <= maxColumn; j++) {
				dp[i][j] = dp[i - 1][j];
				if (j - 1 >= 0) {
					dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MODULO;
				}
				if (j + 1 <= maxColumn) {
					dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % MODULO;
				}
			}
		}
		return dp[steps][0];
	}
	/// <summary>
	/// 1310 子数组异或查询
	/// </summary>
	/// <param name="arr"></param>
	/// <param name="queries"></param>
	/// <returns></returns>
	vector<int> xorQueries(vector<int>& arr, vector<vector<int>>& queries) {
		vector<int> xornum(arr.size() + 1);
		xornum[0] = 0;
		for (int i = 1; i < xornum.size(); ++i) {
			xornum[i] = xornum[i - 1] ^ arr[i - 1];
		}
		vector<int> ret;
		for (int i = 0; i < queries.size(); ++i) {
			int tmp = xornum[queries[i][0]] ^ xornum[queries[i][1] + 1];
			ret.push_back(tmp);
		}
		return ret;
	}
	/// <summary>
	/// 1482 制作m数花所需要的最短时间
	/// </summary>
	/// <param name="bloomDay"></param>
	/// <param name="m"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	int minDays(vector<int>& bloomDay, int m, int k) {
		int n = bloomDay.size();
		if (n < m * k)
			return -1;
		int flowerm = 0;

		int left = 1, right = 1;
		for (int it : bloomDay)
			right = max(right, it);

		while (left < right)
		{
			int days = (left + right) / 2;
			int tmp = 0;
			int flowerk = 0;
			int i = 0;

			while (i < bloomDay.size()) {
				while (i < bloomDay.size() && bloomDay[i] <= days) {
					flowerk++;
					if (flowerk == k) {
						tmp++;
						flowerk = 0;
					}
					i++;
				}
				flowerk = 0;
				i++;
			}

			if (tmp < m)
				left = days + 1;
			else
				right = days;
		}
		return left;
	}	
	/// <summary>
	/// 1486  数组异或操作
	/// </summary>
	/// <param name="n"></param>
	/// <param name="start"></param>
	/// <returns></returns>
	int xorOperation(int n, int start) {
		int ret = 0;
		for (int i = 0; i < n; i++) {
			ret ^= (start + 2 * i);
		}
		return ret;
	}
	/// <summary>
	///1720 解码异或后的数组 
	/// </summary>
	/// <param name="encoded"></param>
	/// <param name="first"></param>
	/// <returns></returns>
	vector<int> decode(vector<int>& encoded, int first) {
		int n = encoded.size();
		vector<int>  arr(n + 1);
		arr[0] = first;
		for (int i = 0; i < n; i++) {
			arr[i + 1] = arr[i] ^ encoded[i];
		}
		return arr;
	}
	
	/// <summary>
	/// 1723 完成所有工作得最短时间
	/// </summary>
	/// <param name="jobs"></param>
	/// <param name="workloads"></param>
	/// <param name="idx"></param>
	/// <param name="limit"></param>
	/// <returns></returns>
	bool backtrack(vector<int>& jobs, vector<int>& workloads, int idx, int limit) {
		if (idx >= jobs.size()) {
			return true;
		}

		int cur = jobs[idx];
		for (auto& workload : workloads) {
			if (workload + cur <= limit) {
				workload += cur;
				if (backtrack(jobs, workloads, idx + 1, limit)) {
					return true;
				}
				workload -= cur;
			}
			if (workload == 0 || workload + cur == limit) {
				break;
			}
		}
		return false;
	}

	bool check(vector<int>& jobs, int k, int limit) {
		vector<int> workloads(k, 0);
		return backtrack(jobs, workloads, 0, limit);
	}

	int minimumTimeRequired(vector<int>& jobs, int k) {
		sort(jobs.begin(), jobs.end(), greater<int>());
		int l = jobs[0], r = accumulate(jobs.begin(), jobs.end(), 0);
		while (l < r) {
			int mid = (l + r) >> 1;
			if (check(jobs, k, mid)) {
				r = mid;
			}
			else {
				l = mid + 1;
			}
		}
		return l;
	}
	
	
	/// <summary>
	/// 1734 解码异或后的排序
	/// </summary>
	/// <param name="encoded"></param>
	/// <returns></returns>
	vector<int> decode(vector<int>& encoded) {
		int n = encoded.size();
		vector<int> ret(n + 1);
		int s = 0;
		for (int i = 1; i < n; i += 2) {
			//cout<<encoded[i]<<endl;
			s ^= encoded[i];
			//cout<<s<<endl<<endl;
		}     

		int num = 0;
		for (int i = 1; i <= (n + 1); ++i)
			num ^= i;

		ret[0] = num ^ s;
		for (int i = 1; i < n + 1; i++) {
			ret[i] = ret[i - 1] ^ encoded[i - 1];
		}

		return ret;

	}
    /// <summary>
    /// 面试题17.21
    /// </summary>
    /// <param name="height"></param>
    /// <returns></returns>
    int trap(vector<int>& height) {
        int n = height.size();
        if (n <= 2)
            return 0;
        int max = 0;
        int water = 0;
        int i = 0;
        while (i < n) {
            if (height[i] > max) {
                max = height[i];
            }
            else {
                water += max - height[i];
            }
            ++i;
        }

        --i;
        int _max = 0;
        while (height[i] != max) {
            if (height[i] >= _max) {
                _max = height[i];
                water -= max - height[i];
            }
            else {
                water -= (max - _max);
            }
            --i;
        }
        return water;

    }
	
	
	/// <summary>
	/// LCP 28 采购方案
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	int purchasePlans(vector<int>& nums, int target) {
		int n = nums.size();
		int ret = 0;
		sort(nums.begin(), nums.end());
		int right = nums.size() - 1;
		for (int left = 0; left < right && nums[left] < target; left++) {
			while (right > left && nums[left] + nums[right] > target) {
				right--;
			}
			ret = (ret + right - left) % 1000000007;
		}
		return ret;
	}
};

class Solution {
private:
    vector<vector<int>> result;
    vector<int> path;

    void backtracking(vector<int>& nums, int startIndex, vector<bool>& used) {
        result.push_back(path);
        for (int i = startIndex; i < nums.size(); i++) {
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false) {
                continue;
            }
            path.push_back(nums[i]);
            used[i] = true;
            backtracking(nums, i + 1, used);
            used[i] = false;
            path.pop_back();
        }
    }

public:
    vector<vector<int>> subsetsWithDup(vector<int>& nums) {
        result.clear();
        path.clear();
        vector<bool> used(nums.size(), false);
        sort(nums.begin(), nums.end()); // 去重需要排序
        backtracking(nums, 0, used);
        return result;
    }
};


/// <summary>
/// 77 组合
/// </summary>
class Solution {
private:
    vector<int> path;
    vector<vector<int>> result;
public:

    void dfs(int n, int k, int curpos) {
        if (path.size() + n - curpos + 1 < k) {
            return;
        }

        if (path.size() == k) {
            result.push_back(path);
            return;
        }

        path.push_back(curpos);
        dfs(n, k, curpos + 1);
        path.pop_back();
        dfs(n, k, curpos + 1);

    }
    vector<vector<int>> combine(int n, int k) {
        dfs(n, k, 1);
        return result;
    }
};

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
