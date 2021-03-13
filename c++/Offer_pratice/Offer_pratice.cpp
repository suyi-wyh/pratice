﻿// Offer_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<StlLock.h>
#include <stack>
#include <list>
#include<StlLock.h>
#include<vector>

using namespace std;
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
};


int main()
{
    std::cout << "Hello World!\n";
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
