// Offer_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<StlLock.h>
#include <stack>
#include <list>
#include<StlLock.h>
#include<vector>
#include <unordered_set>
#include<algorithm>
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
