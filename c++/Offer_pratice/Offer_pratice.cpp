// Offer_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<StlLock.h>
#include <stack>
#include <list>
#include<StlLock.h>
#include<vector>
#include <unordered_set>
#include<unordered_map>
#include<map>
#include<algorithm>
#include<set>
#include<string>
#include<stdint.h>
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
	/// Offer 15 二进制中1的个数
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int hammingWeight(uint32_t n) {
		int ret = 0;
		while (n) {
			n = n & (n - 1);
			ret++;
		}
		return ret;
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
	///  剑指offer 38 字符串的排列
	/// </summary>
	/// <param name="s"></param>
	/// <param name="i"></param>
	/// <param name="ret"></param>
	/// <param name="flag"></param>
	/// <param name="curstr"></param>
	void backtrack(const string& s, const int i, vector<string>& ret, vector<int>& flag, string& curstr)
	{
		if (i == s.size()) {
			ret.push_back(curstr);
			return;
		}

		for (int j = 0; j < s.size(); ++j) {
			if (flag[j] || (j > 0 && !flag[j - 1] && s[j - 1] == s[j])) {
				continue;
			}

			flag[j] = true;
			curstr.push_back(s[j]);
			backtrack(s, i + 1, ret, flag, curstr);
			curstr.pop_back();
			flag[j] = false;
		}
	}

	vector<string> permutation(string s) {
		vector<string> ret;
		vector<int> flag(s.size(), 0);
		string curstr;
		sort(s.begin(), s.end());
		backtrack(s, 0, ret, flag, curstr);
		return ret;
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
	/// 5 最长回文子串
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	string longestPalindrome(string s) {
		int n = s.size();
		if (n < 2)
			return s;

		int begin = 0;
		int maxlen = 1;

		vector< vector<bool> > flag(n, vector<bool>(n));
		for (int i = 0; i < n; ++i)
			flag[i][i] = true;

		for (int len = 2; len <= n; ++len) { //长度
			for (int i = 0; i < n; ++i) { //左边界
				int j = i + len - 1;          //计算右边界

				if (j >= n)
					break;

				if (s[i] != s[j])
					flag[i][j] = false;
				else {
					if (len > 2)
						flag[i][j] = flag[i + 1][j - 1];
					else
						flag[i][j] = true;
				}

				if (flag[i][j] && j - i + 1 > maxlen) {
					begin = i;
					maxlen = j - i + 1;
				}
			}
		}
		return s.substr(begin, maxlen);
	}
	/// <summary>
	/// 10 正则表达式匹配
	/// </summary>
	/// <param name="s"></param>
	/// <param name="p"></param>
	/// <returns></returns>
	bool isMatch(string s, string p) {
		int m = s.size();
		int n = p.size();
		if (n == 0 && m == 0)
			return true;

		if (n == 0)
			return false;

		vector< vector<bool> > flag(m + 1, vector<bool>(n + 1));

		// 初始化
		flag[0][0] = true;
		for (int i = 1; i <= n; ++i) {
			if (p[i - 1] == '*') {
				flag[0][i] = flag[0][i - 2];
			}
			else
				flag[0][i] = false;
		}

		for (int i = 1; i <= m; ++i)
			flag[i][0] = false;

		for (int i = 1; i <= m; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
					flag[i][j] = flag[i - 1][j - 1];

				}
				else if (p[j - 1] == '*') {
					flag[i][j] = flag[i][j - 2] || flag[i][j - 1]
						|| (s[i - 1] == p[j - 2] || p[j - 2] == '.') && (flag[i - 1][j - 1] || flag[i - 1][j]);
				}
				else
					flag[i][j] = false;
			}
		}
		for (int i = 0; i <= m; ++i) {
			for (int j = 0; j <= n; ++j)
				cout << flag[i][j] << "  ";
			cout << "xiayihang" << endl;
		}
		return flag[m][n];
	}
	/// <summary>
	/// 11 盛最多谁的容器
	/// </summary>
	/// <param name="height"></param>
	/// <returns></returns>
	int maxArea(vector<int>& height) {
		int right = height.size() - 1;
		int left = 0;
		int ret = 0;
		while (right > left) {
			int tmp = min(height[right], height[left]) * (right - left);
			ret = max(ret, tmp);
			if (height[right] > height[left])
				left++;
			else
				right--;
		}
		return ret;
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
	/// 65 有效数字
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	bool isNumber(string s) {
		char c = s.back();
		if (c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z' || c == '+' || c == '-') return false;
		if (s.size() > 1 && s[0] == '0' && s[1] == 'x') return false;
		double d;
		char buf[20];
		return sscanf(s.c_str(), "%f%s", &d, buf) == 1;
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
	/// 121 买卖股票的最佳时机
	/// </summary>
	/// <param name="prices"></param>
	/// <returns></returns>
	int maxProfit(vector<int>& prices) {
		int n = prices.size();
		vector<int> dp(n);
		dp[0] = 0;
		int curm = prices[0];
		for (int i = 1; i < n; ++i) {
			dp[i] = max(dp[i - 1], prices[i] - curm);
			if (prices[i] < curm)
				curm = prices[i];
		}

		return dp[n - 1];
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
	/// 141 环形链表
	/// </summary>
	/// <param name="head"></param>
	/// <returns></returns>
	bool hasCycle(ListNode* head) {
		ListNode* fast = head;
		ListNode* slow = head;

		while (fast != nullptr && fast->next != nullptr) {
			fast = fast->next->next;
			slow = slow->next;
			if (fast == slow)
				return true;
		}

		return false;
	}
	/// <summary>
	/// 149 直线上最多的点数
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	int gcd(int a, int b) {
		return b ? gcd(b, a % b) : a;
	}

	int maxPoints(vector<vector<int>>& points) {
		int n = points.size();
		if (n <= 2) {
			return n;
		}
		int ret = 0;
		for (int i = 0; i < n; i++) {
			if (ret >= n - i || ret > n / 2) {
				break;
			}
			unordered_map<int, int> mp;
			for (int j = i + 1; j < n; j++) {
				int x = points[i][0] - points[j][0];
				int y = points[i][1] - points[j][1];
				if (x == 0) {
					y = 1;
				}
				else if (y == 0) {
					x = 1;
				}
				else {
					if (y < 0) {
						x = -x;
						y = -y;
					}
					int gcdXY = gcd(abs(x), abs(y));
					x /= gcdXY, y /= gcdXY;
				}
				mp[y + x * 20001]++;
			}
			int maxn = 0;
			for (auto& [_, num] : mp) {
				maxn = max(maxn, num + 1);
			}
			ret = max(ret, maxn);
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
	/// 160 相交链表
	/// </summary>
	/// <param name="headA"></param>
	/// <param name="headB"></param>
	/// <returns></returns>
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
		int Alength = 0;
		int Blength = 0;
		ListNode* A = headA;
		ListNode* B = headB;
		while (A != nullptr) {
			Alength++;
			A = A->next;
		}
		while (B != nullptr) {
			Blength++;
			B = B->next;
		}

		if (Alength > Blength) {
			for (int i = 0; i < Alength - Blength; ++i)
				headA = headA->next;
		}
		else {
			for (int i = 0; i < Blength - Alength; ++i)
				headB = headB->next;
		}

		while (headA != nullptr && headB != nullptr) {
			if (headA == headB)
				return headB;
			headA = headA->next;
			headB = headB->next;
		}
		return nullptr;
	}
	/// <summary>
	/// 168 excel列表名称
	/// </summary>
	/// <param name="columnNumber"></param>
	/// <returns></returns>
	string convertToTitle(int columnNumber) {
		string ret;
		while (columnNumber) {
			columnNumber--;
			int tmp = columnNumber % 26;
			ret.push_back(('A' + tmp));
			columnNumber /= 26;
		}
		reverse(ret.begin(), ret.end());
		return ret;
	}
	/// <summary>
	/// 169 多数元素
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	int majorityElement(vector<int>& nums) {
		int n = nums.size();
		int cur = nums[0];
		int curn = 1;
		for (int i = 1; i < n; ++i) {
			nums[i] == cur ? curn++ : curn--;
			if (curn < 0) {
				cur = nums[i];
				curn = 1;
			}

		}
		return cur;

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
	/// 203 移除链表元素
	/// </summary>
	/// <param name="head"></param>
	/// <param name="val"></param>
	/// <returns></returns>
	ListNode* removeElements(ListNode* head, int val) {
		ListNode* pre = new ListNode(-1, head);
		ListNode* cur = head;
		head = pre;
		while (cur != nullptr) {
			if (cur->val == val) {
				pre->next = cur->next;
				delete cur;
				cur = pre->next;
			}
			else {
				pre = cur;
				cur = cur->next;
			}
		}
		return head->next;
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
	/// 200 岛屿数量
	/// </summary>
	/// <param name="grid"></param>
	/// <param name="i"></param>
	/// <param name="j"></param>
	void dfs(vector<vector<char>>& grid, int i, int j) {
		grid[i][j] = 0;
		if (i + 1 < grid.size() && grid[i + 1][j] == '1')
			dfs(grid, i + 1, j);
		if (i - 1 >= 0 && grid[i - 1][j] == '1')
			dfs(grid, i - 1, j);
		if (j + 1 < grid[0].size() && grid[i][j + 1] == '1')
			dfs(grid, i, j + 1);
		if (j - 1 >= 0 && grid[i][j - 1] == '1')
			dfs(grid, i, j - 1);

	}
	int numIslands(vector<vector<char>>& grid) {
		int ret = 0;
		for (int i = 0; i < grid.size(); ++i) {
			for (int j = 0; j < grid[0].size(); ++j) {
				if (grid[i][j] == '1') {
					ret++;
					dfs(grid, i, j);
				}
			}
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
	/// 231 2的幂
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	bool isPowerOfTwo(int n) {
		return n > 0 && (n & -n) == n;
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
	/// 278 第一个错误的版本
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int firstBadVersion(int n) {
		int left = 1;
		int right = n;
		while (left < right) {
			int mid = left + (right - left) / 2;
			isBadVersion(mid) ? right = mid : left = mid + 1;
		}
		return right;
	}
	/// <summary>
	/// 279 完全平方数
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int numSquares(int n) {

		vector<int> num(n + 1);

		for (int i = 0; i <= n; ++i) {
			num[i] = i;
		}

		for (int i = 1; i <= sqrt(n); ++i) {
			for (int j = i * i; j <= n; ++j) {
				num[j] = min(num[j], num[j - i * i] + 1);
			}
		}

		return num[n];
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
	/// 342 4的幂
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	bool isPowerOfFour(int n) {
		return n > 0 && (n & (n - 1)) == 0 && n % 3 == 1;
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
	/// 374 猜数字大小
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	int guessNumber(int n) {
		int left = 0;
		int right = n;
		while (left < right) {
			int mid = left + (right - left) / 2;
			int flag = guess(mid);
			if (flag == 0)
				return mid;
			else {
				if (flag == 1)
					left = mid + 1;
				else
					right = mid - 1;
			}
		}
		return left + (right - left) / 2;
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
	/// 401 二进制手表
	/// </summary>
	/// <param name="turnedOn"></param>
	/// <returns></returns>
	vector<string> readBinaryWatch(int turnedOn) {
		vector<string> ret;
		for (int i = 0; i < 12; ++i) {
			for (int j = 0; j < 60; ++j) {
				if (__builtin_popcount(i) + __builtin_popcount(j) == turnedOn) {
					ret.push_back(to_string(i) + ":" + (j >= 10 ? "" : "0") + to_string(j));
				}
			}
		}
		return ret;
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
	/// 461 汉明距离
	/// </summary>
	/// <param name="x"></param>
	/// <param name="y"></param>
	/// <returns></returns>
	int hammingDistance(int x, int y) {
		int ret = 0, s = x ^ y;
		while (s) {
			s = s & (s - 1);
			ret++;
		}
		return ret;
	}
	/// <summary>
	/// 474 0和1
	/// </summary>
	/// <param name="strs"></param>
	/// <param name="m"></param>
	/// <param name="n"></param>
	/// <returns></returns>
	int findMaxForm(vector<string>& strs, int m, int n) {
		vector< vector<int> >  flag(strs.size(), vector<int>(2));
		//统计0和1
		for (int i = 0; i < strs.size(); ++i) {
			int zerom = 0;
			int onen = 0;
			for (char it : strs[i]) {
				if (it == '0')
					zerom++;
				else
					onen++;
			}
			flag[i][0] = zerom;
			flag[i][1] = onen;
		}
		
		vector< vector< vector<int> > > bag(strs.size() + 1, vector<vector<int>>(m + 1, vector<int>(n + 1)));
		for (int i = 1; i <= strs.size(); ++i) {
			int zeros = flag[i - 1][0];
			int ones = flag[i - 1][1];
			for (int j = 0; j <= m; ++j) {
				for (int k = 0; k <= n; ++k) {
					bag[i][j][k] = bag[i - 1][j][k];
					if (j >= zeros && k >= ones) {
						bag[i][j][k] = max(bag[i][j][k], bag[i - 1][j - zeros][k - ones] + 1);
					}
				}
			}
		}
		return bag[strs.size()][m][n];
	}
	/// <summary>
	/// 477 汉明距离总和
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	int totalHammingDistance(vector<int>& nums) {
		int ret = 0;
		int n = nums.size();
		for (int i = 0; i < 30; ++i) {
			int tmp = 0;
			for (int it : nums) {
				tmp += (it >> i) & 1;
			}
			ret += tmp * (n - tmp);
		}
		return ret;
	}
	/// <summary>
	/// 483 最小好进制
	/// </summary>
	/// <param name="n"></param>
	/// <returns></returns>
	string smallestGoodBase(string n) {
		long nVal = stol(n);
		int mMax = floor(log(nVal) / log(2));
		for (int m = mMax; m > 1; m--) {
			int k = pow(nVal, 1.0 / m);
			long mul = 1, sum = 1;
			for (int i = 0; i < m; i++) {
				mul *= k;
				sum += mul;
			}
			if (sum == nVal) {
				return to_string(k);
			}
		}
		return to_string(nVal - 1);
	}
	/// <summary>
	/// 494 目标和
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="target"></param>
	/// <param name="curtarget"></param>
	/// <param name="i"></param>
	/// <param name="ret"></param>
	/// <param name="flag"></param>
	void func(const vector<int>& nums, int target, int curtarget, int i, int& ret, bool flag) {
		if (flag && curtarget == target) {
			ret++;
		}
		if (i >= nums.size())
			return;
		flag = true;
		func(nums, target, curtarget - 2 * nums[i], i + 1, ret, flag);
		flag = false;
		func(nums, target, curtarget, i + 1, ret, flag);
	}
	int findTargetSumWays(vector<int>& nums, int target) {
		int ret = 0;
		int curtarget = 0;
		int i = 0;
		bool flag = true;
		for (int it : nums)
			curtarget += it;

		func(nums, target, curtarget, i, ret, flag);
		return ret;
	}
	/// <summary>
	/// 518 零钱兑换Ⅱ
	/// </summary>
	/// <param name="amount"></param>
	/// <param name="coins"></param>
	/// <returns></returns>
	int change(int amount, vector<int>& coins) {
		int n = coins.size();
		vector<int> dp(amount + 1);
		dp[0] = 1;
		for (int i = 0; i < n; ++i) {
			for (int j = coins[i]; j <= amount; ++j) {
				dp[j] += dp[j - coins[i]];
			}
		}
		return dp[amount];
	}
	/// <summary>
	/// 523 连续的子数组和
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	bool checkSubarraySum(vector<int>& nums, int k) {
		int n = nums.size();
		if (n < 2)
			return false;

		vector<int> sums(n + 1);
		sums[0] = 0;
		for (int i = 1; i < sums.size(); ++i) {
			sums[i] = sums[i - 1] + nums[i - 1];
		}

		unordered_map<int, int> mod;
		for (int i = 1; i < sums.size(); ++i) {
			int m = sums[i] % k;
			if (i >= 2 && !m)
				return true;
			if (mod.count(m)) {
				int ii = mod[m];
				if (i - ii >= 2)
					return true;
			}
			else
				mod.insert(make_pair(m, i));
		}

		return false;
	}
	/// <summary>
	/// 525 连续数组
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	int findMaxLength(vector<int>& nums) {
		if (nums.size() == 1) {
			return  0;
		}
		int ret = 0;

		// 前缀和 之前一共有多少个1
		vector<int> sum(nums.size() + 1);
		sum[0] = 0;
		for (int i = 1; i < sum.size(); ++i)
			sum[i] = sum[i - 1] + nums[i - 1];
		unordered_map<int, int> mp;

		for (int i = 0; i < sum.size(); ++i) {
			if (i - sum[i] == sum[i])
				ret = max(ret, i);
			//i-sum[i]是0的个数 -sum[i]   0比1 多几个  i 前面一共有几个数
			else {
				if (mp.count(i - sum[i] * 2))
					ret = max(ret, i - mp[i - sum[i] * 2]);
				else
					mp.insert(make_pair(i - sum[i] - sum[i], i));
			}
		}
		return ret;
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
	/// 543  二叉树的直径
	/// </summary>
	/// <param name="root"></param>
	/// <param name="maxN"></param>
	/// <returns></returns>
	int Order(TreeNode* root, int& maxN) {
		if (root == nullptr)
			return 0;

		int left = Order(root->left, maxN);
		int right = Order(root->right, maxN);

		maxN = max(maxN, left + right + 1);

		return max(left, right) + 1;

	}
	int diameterOfBinaryTree(TreeNode* root) {
		int ret = 0;
		Order(root, ret);
		return ret - 1;
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
	/// 664 奇怪的打印机
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	int strangePrinter(string s) {
		int n = s.length();
		vector<vector<int>> f(n, vector<int>(n));
		for (int i = n - 1; i >= 0; i--) {
			f[i][i] = 1;
			for (int j = i + 1; j < n; j++) {
				if (s[i] == s[j]) {
					f[i][j] = f[i][j - 1];
				}
				else {
					int minn = INT_MAX;
					for (int k = i; k < j; k++) {
						minn = min(minn, f[i][k] + f[k + 1][j]);
					}
					f[i][j] = minn;
				}
			}
		}
		return f[0][n - 1];
	}
	/// <summary>
	/// 692 前k个高频单词
	/// </summary>
	/// <param name="words"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	vector<string> topKFrequent(vector<string>& words, int k) {
		map<string, int> dict;
		for (string it : words)
			dict[it]++;

		vector<string> ret;
		for ( auto it : dict)
			ret.push_back(it.first);

		sort(ret.begin(), ret.end(), [&](const string& a, const string& b)->bool {
			return dict[a] == dict[b] ? a<b : dict[a]>dict[b]; });
		ret.erase(ret.begin() + k, ret.end());
		return ret;
	}
	
	/// <summary>
	/// 752 开锁转盘锁
	/// </summary>
	/// <param name="deadends"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	int openLock(vector<string>& deadends, string target) {
		if (target == "0000") {
			return 0;
		}

		unordered_set<string> dead(deadends.begin(), deadends.end());
		if (dead.count("0000")) {
			return -1;
		}

		auto num_prev = [](char x) -> char {
			return (x == '0' ? '9' : x - 1);
		};
		auto num_succ = [](char x) -> char {
			return (x == '9' ? '0' : x + 1);
		};

		// 枚举 status 通过一次旋转得到的数字
		auto get = [&](string& status) -> vector<string> {
			vector<string> ret;
			for (int i = 0; i < 4; ++i) {
				char num = status[i];
				status[i] = num_prev(num);
				ret.push_back(status);
				status[i] = num_succ(num);
				ret.push_back(status);
				status[i] = num;
			}
			return ret;
		};

		queue<pair<string, int>> q;
		q.emplace("0000", 0);
		unordered_set<string> seen = { "0000" };

		while (!q.empty()) {
			auto [status, step] = q.front();
			q.pop();
			for (auto&& next_status : get(status)) {
				if (!seen.count(next_status) && !dead.count(next_status)) {
					if (next_status == target) {
						return step + 1;
					}
					q.emplace(next_status, step + 1);
					seen.insert(move(next_status));
				}
			}
		}
		return -1;
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
	/// 810 黑板异或游戏
	/// </summary>
	/// <param name="nums"></param>
	/// <returns></returns>
	bool xorGame(vector<int>& nums) {
		if (nums.size() % 2 == 0) {
			return true;
		}
		int xorsum = 0;
		for (int num : nums) {
			xorsum ^= num;
		}
		return xorsum == 0;
	}
	/// <summary>
	/// 815 公交路线
	/// </summary>
	/// <param name="routes"></param>
	/// <param name="source"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
		if (source == target) {
			return 0;
		}

		int n = routes.size();
		vector<vector<int>> edge(n, vector<int>(n));
		unordered_map<int, vector<int>> rec;
		for (int i = 0; i < n; i++) {
			for (int site : routes[i]) {
				for (int j : rec[site]) {
					edge[i][j] = edge[j][i] = true;
				}
				rec[site].push_back(i);
			}
		}

		vector<int> dis(n, -1);
		queue<int> que;
		for (int bus : rec[source]) {
			dis[bus] = 1;
			que.push(bus);
		}
		while (!que.empty()) {
			int x = que.front();
			que.pop();
			for (int y = 0; y < n; y++) {
				if (edge[x][y] && dis[y] == -1) {
					dis[y] = dis[x] + 1;
					que.push(y);
				}
			}
		}

		int ret = INT_MAX;
		for (int bus : rec[target]) {
			if (dis[bus] != -1) {
				ret = min(ret, dis[bus]);
			}
		}
		return ret == INT_MAX ? -1 : ret;
	}
	/// <summary>
	/// 852 山脉数组的峰顶索引
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	int peakIndexInMountainArray(vector<int>& arr) {
		int left = 0;
		int right = arr.size() - 1;

		while (left < right) {
			int mid = left + (right - left) / 2;
			if (arr[mid] > arr[mid + 1] && arr[mid] > arr[mid - 1])
				return mid;

			if (arr[mid] < arr[mid + 1])
				left = mid + 1;
			else
				right = mid;
		}
		return right;
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
	/// 877 石子游戏
	/// </summary>
	/// <param name="piles"></param>
	/// <returns></returns>
	bool stoneGame(vector<int>& piles) {
		return 1;
	}
	/// <summary>
	///  879 盈利计划
	/// </summary>
	/// <param name="n"></param>
	/// <param name="minProfit"></param>
	/// <param name="group"></param>
	/// <param name="profit"></param>
	/// <returns></returns>
	int profitableSchemes(int n, int minProfit, vector<int>& group, vector<int>& profit) {
		int len = group.size(), MOD = (int)1e9 + 7;
		vector<vector<vector<int>>> dp(len + 1, vector<vector<int>>(n + 1, vector<int>(minProfit + 1)));
		dp[0][0][0] = 1;
		for (int i = 1; i <= len; i++) {
			int members = group[i - 1], earn = profit[i - 1];
			for (int j = 0; j <= n; j++) {
				for (int k = 0; k <= minProfit; k++) {
					if (j < members) {
						dp[i][j][k] = dp[i - 1][j][k];
					}
					else {
						dp[i][j][k] = (dp[i - 1][j][k] + dp[i - 1][j - members][max(0, k - earn)]) % MOD;
					}
				}
			}
		}
		int sum = 0;
		for (int j = 0; j <= n; j++) {
			sum = (sum + dp[len][j][minProfit]) % MOD;
		}
		return sum;
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
	/// 909 蛇梯棋
	/// </summary>
	/// <param name="id"></param>
	/// <param name="n"></param>
	/// <returns></returns>
	pair<int, int> id2rc(int id, int n) {
		int r = (id - 1) / n, c = (id - 1) % n;
		if (r % 2 == 1) {
			c = n - 1 - c;
		}
		return { n - 1 - r, c };
	}

	int snakesAndLadders(vector<vector<int>>& board) {
		int n = board.size();
		vector<int> vis(n * n + 1);
		queue<pair<int, int>> q;
		q.emplace(1, 0);
		while (!q.empty()) {
			auto p = q.front();
			q.pop();
			for (int i = 1; i <= 6; ++i) {
				int nxt = p.first + i;
				if (nxt > n * n) { // 超出边界
					break;
				}
				auto rc = id2rc(nxt, n); // 得到下一步的行列
				if (board[rc.first][rc.second] > 0) { // 存在蛇或梯子
					nxt = board[rc.first][rc.second];
				}
				if (nxt == n * n) { // 到达终点
					return p.second + 1;
				}
				if (!vis[nxt]) {
					vis[nxt] = true;
					q.emplace(nxt, p.second + 1); // 扩展新状态
				}
			}
		}
		return -1;
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
	/// 1035 不相交的线
	/// </summary>
	/// <param name="nums1"></param>
	/// <param name="nums2"></param>
	/// <returns></returns>
	int maxUncrossedLines(vector<int>& nums1, vector<int>& nums2) {
		int n1 = nums1.size();
		int n2 = nums2.size();
		vector<vector<int>> ans(n1 + 1, vector<int>(n2 + 1));
		for (int i = 1; i <= n1; ++i) {
			for (int j = 1; j <= n2; ++j) {
				if (nums1[i - 1] == nums2[j - 1])
					ans[i][j] = ans[i - 1][j - 1] + 1;
				else
					ans[i][j] = max(ans[i][j - 1], ans[i - 1][j]);
			}
		}
		return ans[n1][n2];
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
	/// 1049  最后一块石头的重量Ⅱ  
	/// </summary>
	/// <param name="stones"></param>
	/// <returns></returns>
	int lastStoneWeightII(vector<int>& stones) {
		int n = stones.size();
		int sum = accumulate(stones.begin(), stones.end(), 0);

		vector<vector<bool>> bag(n + 1, vector<bool>(sum / 2 + 1));

		// 初始化
		bag[0][0] = true;
		for (int i = 1; i <= sum / 2; ++i)
			bag[0][i] = false;

		for (int i = 1; i <= n; ++i) {
			for (int j = 0; j <= sum / 2; ++j) {
				if (j < stones[i - 1]) {
					bag[i][j] = bag[i - 1][j];
				}
				else {
					bag[i][j] = bag[i - 1][j] || bag[i - 1][j - stones[i - 1]];
				}
			}
		}

		for (int i = sum / 2; i >= 0; --i) {
			if (bag[n][i])
				return sum - i * 2;
		}
		return 0;
	}
	/// <summary>
	/// 1074 元素和为目标值的子矩阵数量
	/// </summary>
	/// <param name="nums"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	int subarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> mp;
		mp[0] = 1;
		int count = 0, pre = 0;
		for (auto& x : nums) {
			pre += x;
			if (mp.find(pre - k) != mp.end()) {
				count += mp[pre - k];
			}
			mp[pre]++;
		}
		return count;
	}

	int numSubmatrixSumTarget(vector<vector<int>>& matrix, int target) {
		int ans = 0;
		int m = matrix.size(), n = matrix[0].size();
		for (int i = 0; i < m; ++i) { // 枚举上边界
			vector<int> sum(n);
			for (int j = i; j < m; ++j) { // 枚举下边界
				for (int c = 0; c < n; ++c) {
					sum[c] += matrix[j][c]; // 更新每列的元素和
				}
				ans += subarraySum(sum, target);
			}
		}
		return ans;
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
	/// 1190 反转每对括号间的子串
	/// </summary>
	/// <param name="s"></param>
	/// <returns></returns>
	string reverseParentheses(string s) {
		string ret;
		if (s.size() == 0)
			return ret;

		stack<string> stk;
		for (char it : s) {
			if (it == '(') {
				stk.push(ret);
				ret.clear();
			}
			else if (it == ')') {
				reverse(ret.begin(), ret.end());
				ret = stk.top() + ret;
				stk.pop();
			}
			else
				ret.push_back(it);
		}
		return ret;
	}
	/// <summary>
	/// 1239 串联字符串的最大长度
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	int maxLength(vector<string>& arr) {
		vector<int> masks;
		for (string& s : arr) {
			int mask = 0;
			for (char ch : s) {
				ch -= 'a';
				if ((mask >> ch) & 1) { // 若 mask 已有 ch，则说明 s 含有重复字母，无法构成可行解
					mask = 0;
					break;
				}
				mask |= 1 << ch; // 将 ch 加入 mask 中
			}
			if (mask > 0) {
				masks.push_back(mask);
			}
		}

		int ans = 0;
		function<void(int, int)> backtrack = [&](int pos, int mask) {
			if (pos == masks.size()) {
				ans = max(ans, __builtin_popcount(mask));
				return;
			}
			if ((mask & masks[pos]) == 0) { // mask 和 masks[pos] 无公共元素
				backtrack(pos + 1, mask | masks[pos]);
			}
			backtrack(pos + 1, mask);
		};
		backtrack(0, 0);
		return ans;
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
	/// 1442 形成两个异或相等的数组的三元组数目
	/// </summary>
	/// <param name="arr"></param>
	/// <returns></returns>
	int countTriplets(vector<int>& arr) {
		int n = arr.size();
		vector<int> s(n + 1);
		for (int i = 0; i < n; ++i) {
			s[i + 1] = s[i] ^ arr[i];
		}
		int ans = 0;
		for (int i = 0; i < n; ++i) {
			for (int k = i + 1; k < n; ++k) {
				if (s[i] == s[k + 1]) {
					ans += k - i;
				}
			}
		}
		return ans;
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
	/// 1449 数位成本和为目标值的最大数
	/// </summary>
	/// <param name="cost"></param>
	/// <param name="target"></param>
	/// <returns></returns>
	string largestNumber(vector<int>& cost, int target) {
		vector<vector<int>> dp(10, vector<int>(target + 1, INT_MIN));
		vector<vector<int>> from(10, vector<int>(target + 1));
		dp[0][0] = 0;
		for (int i = 0; i < 9; ++i) {
			int c = cost[i];
			for (int j = 0; j <= target; ++j) {
				if (j < c) {
					dp[i + 1][j] = dp[i][j];
					from[i + 1][j] = j;
				}
				else {
					if (dp[i][j] > dp[i + 1][j - c] + 1) {
						dp[i + 1][j] = dp[i][j];
						from[i + 1][j] = j;
					}
					else {
						dp[i + 1][j] = dp[i + 1][j - c] + 1;
						from[i + 1][j] = j - c;
					}
				}
			}
		}
		if (dp[9][target] < 0) {
			return "0";
		}
		string ans;
		int i = 9, j = target;
		while (i > 0) {
			if (j == from[i][j]) {
				--i;
			}
			else {
				ans += '0' + i;
				j = from[i][j];
			}
		}
		return ans;
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
	/// 1738 找出第K大的异或坐标值
	/// </summary>
	/// <param name="matrix"></param>
	/// <param name="k"></param>
	/// <returns></returns>
	int kthLargestValue(vector<vector<int>>& matrix, int k) {
		int n = matrix.size();
		int m = matrix[0].size();

		vector<vector<int>> ans(n, vector<int>(m));
		vector<int> ret;
		int tmp = 0;

		for (int i = 0; i < m; ++i) {
			ans[0][i] = tmp = tmp ^ matrix[0][i];
			ret.push_back(ans[0][i]);

		}


		for (int i = 1; i < n; i++) {
			ans[i][0] = matrix[i][0] ^ ans[i - 1][0];
			ret.push_back(ans[i][0]);

		}

		for (int i = 1; i < n; i++) {
			for (int j = 1; j < m; j++) {
				ans[i][j] = ans[i - 1][j] ^ ans[i][j - 1] ^ ans[i - 1][j - 1] ^ matrix[i][j];
				ret.push_back(ans[i][j]);

			}
		}

		sort(ret.begin(), ret.end(), greater<int>());

		return ret[k - 1];
	}
	/// <summary>
	/// 1744 你能在你最喜欢的哪天吃到最喜欢的糖果吗
	/// </summary>
	/// <param name="csum"></param>
	/// <param name="day"></param>
	/// <param name="daily"></param>
	/// <returns></returns>
	bool func(long long csum, int day, int daily) {
		long long dayNum = (long long)(day + 1) * (long long)(daily);
		return csum < dayNum;
	}

	vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
		vector<long long> candiesNum(candiesCount.size());
		vector<bool>  answer;

		candiesNum[0] = candiesCount[0];

		for (int i = 1; i < candiesNum.size(); ++i) {
			candiesNum[i] = candiesNum[i - 1] + candiesCount[i];
		}

		for (auto& it : queries) {
			int type = it[0];
			int day = it[1];
			int daily = it[2];

			long long sum = candiesNum[type];
			long long csum = candiesNum[type] - candiesCount[type];
			// cout<<"sum"<<sum<<"csum"<<csum<<endl;
			answer.push_back(sum > day && func(csum, day, daily));
		}
		return answer;
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
	
	/// <summary>
	/// 牛客 两个字符串间的距离
	/// </summary>
	/// <param name="str1"></param>
	/// <param name="str2"></param>
	/// <returns></returns>
	int minDistance(const string& str1, const string& str2) {
		if (str1.empty() || str2.empty())
			return max(str1.size(), str2.size());
		int n1 = str1.size();
		int n2 = str2.size();
		vector<vector<int>> f(n1 + 1, vector<int>(n2 + 1));
		for (int i = 0; i < f.size(); ++i)
			f[i][0] = i;

		for (int i = 0; i < f[0].size(); ++i)
			f[0][i] = i;
		for (int i = 1; i < f.size(); ++i) {
			for (int j = 1; j < f[0].size(); ++j) {
				f[i][j] = min(f[i - 1][j], f[i][j - 1]) + 1;
				if (str1[i - 1] == str2[j - 1]) {
					f[i][j] = min(f[i][j], f[i - 1][j - 1]);
				}
				else
					f[i][j] = min(f[i][j], f[i - 1][j - 1] + 1);
			}
		}
		return f[n1][n2];

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

/// <summary>
/// 1707 与数组中元素的最大异或值
/// </summary>
class Trie {
public:
	const int L = 30;

	Trie* children[2] = {};
	int min = INT_MAX;

	void insert(int val) {
		Trie* node = this;
		node->min = std::min(node->min, val);
		for (int i = L - 1; i >= 0; --i) {
			int bit = (val >> i) & 1;
			if (node->children[bit] == nullptr) {
				node->children[bit] = new Trie();
			}
			node = node->children[bit];
			node->min = std::min(node->min, val);
		}
	}

	int getMaxXorWithLimit(int val, int limit) {
		Trie* node = this;
		if (node->min > limit) {
			return -1;
		}
		int ans = 0;
		for (int i = L - 1; i >= 0; --i) {
			int bit = (val >> i) & 1;
			if (node->children[bit ^ 1] != nullptr && node->children[bit ^ 1]->min <= limit) {
				ans |= 1 << i;
				bit ^= 1;
			}
			node = node->children[bit];
		}
		return ans;
	}
};
// 字典树  增加了一个保存当前树存的最小节点的值limit 
class Solution {
public:
	vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
		Trie* t = new Trie();
		for (int val : nums) {
			t->insert(val);
		}
		int numQ = queries.size();
		vector<int> ans(numQ);
		for (int i = 0; i < numQ; ++i) {
			ans[i] = t->getMaxXorWithLimit(queries[i][0], queries[i][1]);
		}
		return ans;
	}
};



/// <summary>
/// 1787 使所有确界的异或结果为零
/// </summary>
class Solution {
private:
	// x 的范围为 [0, 2^10)
	static constexpr int MAXX = 1 << 10;
	// 极大值，为了防止整数溢出选择 INT_MAX / 2
	static constexpr int INFTY = INT_MAX / 2;

public:
	int minChanges(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> f(MAXX, INFTY);
		// 边界条件 f(-1,0)=0
		f[0] = 0;

		for (int i = 0; i < k; ++i) {
			// 第 i 个组的哈希映射
			unordered_map<int, int> cnt;
			int size = 0;
			for (int j = i; j < n; j += k) {
				++cnt[nums[j]];
				++size;
			}

			// 求出 t2
			int t2min = *min_element(f.begin(), f.end());

			vector<int> g(MAXX, t2min);
			for (int mask = 0; mask < MAXX; ++mask) {
				// t1 则需要枚举 x 才能求出
				for (auto [x, countx] : cnt) {
					g[mask] = min(g[mask], f[mask ^ x] - countx);
				}
			}

			// 别忘了加上 size
			for_each(g.begin(), g.end(), [&](int& val) {val += size; });
			f = move(g);
		}

		return f[0];
	}
};

/// <summary>
/// 1600 皇位继承顺序
/// </summary>
class ThroneInheritance {
private:
	string cur;
	set<string> death_InheritanceOrder;
	map<string, vector<string>> curorder;

public:
	ThroneInheritance(string kingName) :cur(kingName) {
	}

	void birth(string parentName, string childName) {
		curorder[parentName].push_back(childName);
	}

	void death(string name) {
		death_InheritanceOrder.insert(name);
	}

	vector<string> getInheritanceOrder() {
		vector<string> ret;
		function< void(const string&) >  dfs = [&](const string& str) {
			if (!death_InheritanceOrder.count(str)) {
				ret.push_back(str);
			}

			if (curorder.count(str)) {
				for (const string& it : curorder[str])
					dfs(it);
			}
		};

		dfs(cur);
		return ret;
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
