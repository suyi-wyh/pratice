// leetcode_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

/// <summary>
/// 1 两数之和
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="target"></param>
/// <param name="returnSize"></param>
/// <returns></returns>
int* twoSum(int* nums, int numsSize, int target, int* returnSize)
{
    int* arg = (int*)malloc(sizeof(int) * 2);
    for (int i = 0; i < numsSize; ++i)
        for (int j = i + 1; j < numsSize; ++j)
        {
            if (nums[i] + nums[j] == target)
            {
                arg[0] = i;
                arg[1] = j;
                *returnSize = 2;
                return arg;
            }
        }
    *returnSize = 0;
    return NULL;
}

/// <summary>
/// 567  字符串的排列
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
bool arrcmp(int* a, int* b)
{
    for (int i = 0; i < 26; ++i)
        if (a[i] != b[i])
            return false;
    return true;
}
bool checkInclusion(char* s1, char* s2) {
    int s1len = strlen(s1), s2len = strlen(s2);
    if (s1len > s2len)
        return false;
    int s1arr[26], s2arr[26];
    memset(s1arr, 0, sizeof(s1arr));
    memset(s2arr, 0, sizeof(s2arr));
    for (int i = 0; i < s1len; ++i)
    {
        ++s2arr[s2[i] - 'a'];
        ++s1arr[s1[i] - 'a'];
    }
    if (arrcmp(s1arr, s2arr))
        return true;
    for (int i = 0; i < s2len - s1len; ++i)
    {
        --s2arr[s2[i] - 'a'];
        ++s2arr[s2[i + s1len] - 'a'];
        if (arrcmp(s1arr, s2arr))
            return true;
    }
    return false;
}
/// <summary>
/// 634 子数组最大平均数
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="k"></param>
/// <returns></returns>
double findMaxAverage(int* nums, int numsSize, int k)
{
    double returnNums = 0;
    for (int i = 0; i < k; i++)
        returnNums += nums[i];
    returnNums = (double)returnNums / (double)k;
    double tmp = returnNums;
    for (int i = 0; i < numsSize - k; ++i)
    {
        tmp = (double)((double)(tmp * k) - (double)nums[i] + (double)nums[i + k]) / (double)k;
        if (returnNums < tmp)
            returnNums = tmp;
    }
    return returnNums;
}

/// <summary>
/// 665  非递减数列
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <returns></returns>
bool checkPossibility(int* nums, int numsSize) {
    if (numsSize == 1)
        return true;
    int flag;
    int i = 0;
    for (; i < numsSize - 1; ++i)
    {
        if (nums[i] > nums[i + 1])
        {
            flag = i;
            break;
        }
    }

    if (i == numsSize - 1)
        return true;
    int tmp = nums[flag];
    nums[flag] = nums[flag + 1];
    int j = 0;
    for (; j < numsSize - 1; j++)
    {
        if (nums[j] > nums[j + 1])
            break;
    }
    if (j == numsSize - 1)
        return true;
    int z = 0;
    nums[flag] = nums[flag + 1] = tmp;
    for (; z < numsSize - 1; z++)
    {
        if (nums[z] > nums[z + 1])
            break;
    }
    if (z == numsSize - 1)
        return true;
    else
        return false;
}

/// <summary>
/// 978 最长湍流子数组
/// </summary>
/// <param name="arr"></param>
/// <param name="arrSize"></param>
/// <returns></returns>
int maxTurbulenceSize(int* arr, int arrSize) {
    if (arrSize == 1)
        return 1;
    int left = 0, ret = 1, right = 0;

    while (right < arrSize - 1)
    {
        if (left == right)
        {
            if (arr[left] == arr[left + 1])
                left++;
            right++;
        }
        else
        {
            if (arr[right - 1]<arr[right] && arr[right]>arr[right + 1])
                right++;
            else if (arr[right - 1] > arr[right] && arr[right] < arr[right + 1])
                right++;
            else
                left = right;
        }

        ret = fmax(ret, right - left + 1);
    }
    return ret;
}
/// <summary>
/// 992  k个不同整数的子数组
/// </summary>
/// <param name="A"></param>
/// <param name="ASize"></param>
/// <param name="K"></param>
/// <returns></returns>
int _subarraysWithKDistinct(int* A, int ASize, int K) {

    int* Fre = (int*)malloc((ASize + 1) * sizeof(int));
    memset(Fre, 0, sizeof(int) * (ASize + 1));
    int right = 0, left = 0;
    int count = 0, res = 0;
    while (right < ASize)
    {
        if (Fre[A[right]] == 0)
            ++count;
        ++Fre[A[right]];
        ++right;

        while (count > K)
        {
            Fre[A[left]]--;
            if (Fre[A[left]] == 0)
                count--;
            left++;
        }
        res += right - left;
    }
    return res;
}

int subarraysWithKDistinct(int* A, int ASize, int K) {
    return _subarraysWithKDistinct(A, ASize, K) - _subarraysWithKDistinct(A, ASize, K - 1);
}

/// <summary>
/// 1208  尽可能使字符串相等
/// </summary>
/// <param name="s"></param>
/// <param name="t"></param>
/// <param name="maxCost"></param>
/// <returns></returns>
int equalSubstring(char* s, char* t, int maxCost) {
    int returnNums = 0;
    int cur = 0;
    int cost = 0;

    int i = 0;
    int j = 0;
    while (s && i < strlen(s))
    {

        if (cost <= maxCost)
        {
            cost += abs(s[i] - t[i]);
            i++;
            cur++;
        }
        else if (i > j)
        {
            cost -= abs(s[j] - t[j]);
            j++;
            cur--;
        }
        else {
            j++;
            i++;
        }


        if (cost <= maxCost && cur > returnNums)
            returnNums = cur;
    }
    return returnNums;
}

/// <summary>
/// 1423 可获得的最大点数
/// </summary>
/// <param name="cardPoints"></param>
/// <param name="cardPointsSize"></param>
/// <param name="k"></param>
/// <returns></returns>
int maxScore(int* cardPoints, int cardPointsSize, int k)
{
    int numSize = cardPointsSize - k;
    int nums = 0;
    for (int i = 0; i < numSize; ++i)
        nums += cardPoints[i];
    int sum = nums;
    int cur = nums;
    for (int i = 0; i < k; ++i)
    {
        sum += cardPoints[i + numSize];
        nums = nums - cardPoints[i] + cardPoints[i + numSize];
        if (cur > nums)
            cur = nums;
    }
    return sum - cur;
}


int main()
{
    int a = abs('r' - 'j');
    printf("%d\n", a);
    int b = abs('r' - 'x');
    printf("%d\n", b);
    printf("%d\n", a + b);
    
    double aa = 1.0;
    double bb = 2.0;
    printf("%f", fmax(aa, bb));
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
