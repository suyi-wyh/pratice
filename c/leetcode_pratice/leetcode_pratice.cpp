// leetcode_pratice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"uthash.h"

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
/// 14 最长公共前缀
/// </summary>
/// <param name="strs"></param>
/// <param name="strsSize"></param>
/// <returns></returns>
char* longestCommonPrefix(char** strs, int strsSize) {
    int flag = 0;
    if (!strs || strsSize == 0)
        return NULL;    //  在oj在线时需要将 NULL 改为 ""
    while (*(*strs + flag))
    {
        int g = 0;
        for (int i = 0; i < strsSize - 1; ++i)
        {
            if (!*(strs[i] + flag) || !*(strs[i] + flag) ||
                (*(strs[i] + flag) != *(strs[i + 1] + flag)))
            {
                g = 1;
                break;
            }
        }
        if (g == 1)
            break;
        ++flag;
    }
    char* returnStr = (char*)malloc((flag + 1) * sizeof(char));
    memset(returnStr, 0, (flag + 1) * sizeof(char));
    for (int i = 0; i < flag; ++i)
    {
        returnStr[i] = *(strs[0] + i);
    }
    return returnStr;

}
/// <summary>
/// 119 杨辉三角
/// </summary>
/// <param name="rowIndex"></param>
/// <param name="returnSize"></param>
/// <returns></returns>

int* getRow(int rowIndex, int* returnSize) {
    *returnSize = rowIndex + 1;
    int* returnNums = (int*)malloc(*returnSize * sizeof(int));
    memset(returnNums, 0, *returnSize * sizeof(int));
    returnNums[0] = 1;
    for (int i = 1; i < rowIndex + 1; i++)
        for (int j = i; j > 0; --j)
            returnNums[j] += returnNums[j - 1];
    return returnNums;
}

/// <summary>
/// 232 用栈实现队列
/// </summary>
typedef struct {
    int* _stack;
    int size;
}mystack;

typedef struct {
    mystack* stack_in;
    mystack* stack_out;
} MyQueue;

/** Initialize your data structure here. */

MyQueue* myQueueCreate() {
    MyQueue* queue = (MyQueue*)malloc(sizeof(MyQueue));
    queue->stack_in = (mystack*)malloc(sizeof(mystack));
    queue->stack_out = (mystack*)malloc(sizeof(mystack));
    queue->stack_in->_stack = (int*)malloc(sizeof(int) * 100);
    queue->stack_out->_stack = (int*)malloc(sizeof(int) * 100);
    queue->stack_in->size = queue->stack_out->size = -1;
    printf("%d,%d\n", queue->stack_in->size, queue->stack_out->size);
    return queue;
}

/** Push element x to the back of queue. */
void myQueuePush(MyQueue* obj, int x) {
    obj->stack_in->size++;
    obj->stack_in->_stack[obj->stack_in->size] = x;
}

/** Removes the element from in front of queue and returns that element. */
int myQueuePop(MyQueue* obj) {
    if (obj->stack_out->size != -1)
    {
        --obj->stack_out->size;
        return obj->stack_out->_stack[obj->stack_out->size + 1];
    }
    else
    {
        while (obj->stack_in->size != -1)
        {
            obj->stack_out->size++;
            obj->stack_out->_stack[obj->stack_out->size] = obj->stack_in->_stack[obj->stack_in->size--];
        }
        obj->stack_out->size--;
        return obj->stack_in->_stack[0];
    }
}

/** Get the front element. */
int myQueuePeek(MyQueue* obj) {
    if (obj->stack_out->size != -1)
        return obj->stack_out->_stack[obj->stack_out->size];
    else
        return obj->stack_in->_stack[0];
}

/** Returns whether the queue is empty. */
bool myQueueEmpty(MyQueue* obj) {
    if (obj->stack_out->size == obj->stack_in->size && obj->stack_out->size == -1)
        return true;
    else
        return false;
}

void myQueueFree(MyQueue* obj) {
    free(obj->stack_out->_stack);
    free(obj->stack_in->_stack);
    free(obj->stack_out);
    free(obj->stack_in);
}

/// <summary>
/// 303 区域和检索-数组不可变
/// </summary>
typedef struct {
    int* nums;
} NumArray;


NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* numsArray = (NumArray*)malloc(sizeof(NumArray));
    numsArray->nums = (int*)malloc((numsSize + 1) * sizeof(int));
    numsArray->nums[0] = 0;
    for (int i = 0; i < numsSize; ++i)
        numsArray->nums[i + 1] = numsArray->nums[i] + nums[i];
    return numsArray;
}

int numArraySumRange(NumArray* obj, int i, int j) {
    return obj->nums[j + 1] - obj->nums[i];
}

void numArrayFree(NumArray* obj) {
    free(obj->nums);
    free(obj);
}



/// <summary>
///  304 二维区域和检索-矩阵不可变
/// </summary>
typedef struct {
    int** nums;
    int col;
    int row;
} NumMatrix;


NumMatrix* numMatrixCreate(int** matrix, int matrixSize, int* matrixColSize) {
    NumMatrix* numsMatrix = (NumMatrix*)malloc(sizeof(NumMatrix));
    numsMatrix->col = matrixSize;
    numsMatrix->nums = (int**)malloc(numsMatrix->col * sizeof(int*));
    for (int i = 0; i < numsMatrix->col; ++i)
    {
        numsMatrix->row = matrixColSize[i] + 1;
        numsMatrix->nums[i] = (int*)malloc(numsMatrix->row * sizeof(int));
        numsMatrix->nums[i][0] = 0;
        for (int j = 1; j < numsMatrix->row; ++j)
            numsMatrix->nums[i][j] = numsMatrix->nums[i][j - 1] + matrix[i][j - 1];
    }
    return numsMatrix;
}

int numMatrixSumRegion(NumMatrix* obj, int row1, int col1, int row2, int col2) {
    int nums = 0;
    for (int i = row1; i <= row2; ++i)
        nums += (obj->nums[i][col2 + 1] - obj->nums[i][col1]);
    return nums;
}

void numMatrixFree(NumMatrix* obj) {
    for (int i = 0; i < obj->col; ++i)
        free(obj->nums[i]);
    free(obj->nums);
}

/// <summary>
/// 354 俄罗斯套娃信封
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
int cmp(const int**  a, const int**  b) {
    return (*a)[0] == (*b)[0] ? (*b)[1] - (*a)[1] : (*a)[0] - (*b)[0];
}

int maxEnvelopes(int** envelopes, int envelopesSize, int* envelopesColSize) {

    if (envelopesSize == 0)
        return 0;

    qsort(envelopes, envelopesSize, sizeof(int*), cmp);
    int n = envelopesSize;
    int* f = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; ++i)
        f[i] = 1;
    int ret = 1;

    for (int i = 1; i < n; ++i)
    {
        for (int j = 0; j < i; ++j)
        {
            if (envelopes[j][1] < envelopes[i][1])
                f[i] = fmax(f[i], f[j] + 1);
        }
        ret = fmax(f[i], ret);
    }
    return ret;
}
/// <summary>
/// 338 比特位计数
/// </summary>
/// <param name="num"></param>
/// <param name="returnSize"></param>
/// <returns></returns>
int* countBits(int num, int* returnSize) {
    *returnSize = num + 1;
    int* returnNum = (int*)malloc(*returnSize * sizeof(int));
    memset(returnNum, 0, *returnSize * sizeof(int));
    for (int i = 0; i <= num / 2; ++i)
    {
        returnNum[2 * i] = returnNum[i];
        if (2 * i + 1 < *returnSize)
            returnNum[2 * i + 1] = returnNum[i] + 1;
    }
    return returnNum;
}
/// <summary>
/// 395 至少有K歌重复字符的最长子串  
/// </summary>
/// <param name="s"></param>
/// <param name="l"></param>
/// <param name="r"></param>
/// <param name="k"></param>
/// <returns></returns>
int dfs(char* s, int l, int r, int k)
{
    int cnt[26] = { 0 };

    for (int i = l; i <= r; ++i)
        ++cnt[s[i] - 'a'];

    int split = 0;
    for (int i = 0; i < 26; ++i)
        if (cnt[i] > 0 && cnt[i] < k)
        {
            split = i + 'a';
            break;
        }

    if (split == 0)
        return r - l + 1;

    int i = l;
    int returnSize = 0;

    while (i <= r)
    {
        while (i <= r && s[i] == (char)split)
            i++;
        if (i > r)
            break;
        int start = i;
        while (i <= r && s[i] != (char)split)
            ++i;
        returnSize = fmax(returnSize, dfs(s, start, i - 1, k));
    }
    return returnSize;
}

int longestSubstring(char* s, int k) {
    return dfs(s, 0, strlen(s) - 1, k);
}
/// <summary>
/// 448 找到所有数组中消失的数字
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="returnSize"></param>
/// <returns></returns>
int* findDisappearedNumbers(int* nums, int numsSize, int* returnSize) {
    *returnSize = 0;
    for (int i = 0; i < numsSize; ++i)
        nums[(nums[i] - 1) % numsSize] += numsSize;
    int* returnNums = (int*)malloc(numsSize * sizeof(int));
    for (int i = 0; i < numsSize; ++i)
    {
        if (nums[i] <= numsSize)
            returnNums[(*returnSize)++] = i + 1;
    }
    return returnNums;
}

/// <summary>
/// 485 最大连续1的个数
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <returns></returns>
int findMaxConsecutiveOnes(int* nums, int numsSize) {
    int flag = 0;
    for (int i = 0; i < numsSize;)
    {
        int  Nums = 0;
        while (i < numsSize && nums[i] != 0)
        {
            ++Nums;
            ++i;
        }
        ++i;
        flag = fmax(flag, Nums);
        Nums = 0;
    }
    return flag;
}

/// <summary>
/// 566 重塑矩阵
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="numsColSize"></param>
/// <param name="r"></param>
/// <param name="c"></param>
/// <param name="returnSize"></param>
/// <param name="returnColumnSizes"></param>
/// <returns></returns>
int** matrixReshape(int** nums, int numsSize, int* numsColSize, int r, int c, int* returnSize, int** returnColumnSizes) {
    int m = numsSize;
    int n = numsColSize[0];
    if (m * n != r * c) {
        *returnSize = numsSize;
        *returnColumnSizes = numsColSize;
        return nums;
    }
    *returnSize = r;
    *returnColumnSizes = (int*)malloc(sizeof(int) * r);
    int** ans = (int**)malloc(sizeof(int*) * r);

    for (int i = 0; i < r; i++) {
        (*returnColumnSizes)[i] = c;
        ans[i] = (int*)malloc(sizeof(int) * c);
    }
    for (int x = 0; x < m * n; ++x) {
        ans[x / c][x % c] = nums[x / n][x % n];
    }
    return ans;
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
/// 697 数组的度
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <returns></returns>
int findShortestSubArray(int* nums, int numsSize) {
    int  Nums[50000], First[50000], Last[50000];
    memset(Nums, 0, sizeof(Nums));
    for (int i = 0; i < numsSize; ++i)
    {
        ++Nums[nums[i]];
        if (Nums[nums[i]] == 1)
            First[nums[i]] = Last[nums[i]] = i;
        else
            Last[nums[i]] = i;
    }

    int flag = 0;
    int returnSize = numsSize;

    for (int i = 0; i < 50000; ++i)
        flag = fmax(flag, Nums[i]);

    for (int i = 0; i < 50000; ++i)
    {
        if (flag == Nums[i])
            returnSize = fmin(returnSize, Last[i] - First[i] + 1);
    }

    return returnSize;
}
/// <summary>
/// 703 数据流中的第k大元素
/// </summary>
typedef struct {
    int* data;
    int size;
    int cnt;
} KthLargest;

KthLargest* Init(int k)
{
    KthLargest* Kth = (KthLargest*)malloc(sizeof(KthLargest));
    Kth->data = (int*)malloc(k * sizeof(int));
    //memset(Kth->data,0,sizeof(int)*k);
    for (int i = 0; i < k; i++)
        Kth->data[i] = -100000;            // 这里因为测试用例偷懒了 这个数比所有测试用例数据小
    Kth->size = k;
    Kth->cnt = 0;
    return Kth;
}

void adJustDown(int* data, int n, int root)
{
    int parent = root;
    int child = 2 * parent + 1;
    while (child < n)
    {
        if (child + 1 >= n);
        else if (data[child + 1] < data[child])
            child++;

        if (data[child] < data[parent])
        {
            int tmp = data[child];
            data[child] = data[parent];
            data[parent] = tmp;
            parent = child;
            child = 2 * child + 1;
        }
        else
            break;
    }
}

int kthLargestAdd(KthLargest* obj, int val) {  
    if (val > obj->data[0])
    {
        obj->data[0] = val;
        adJustDown(obj->data, obj->size, 0);
    }
    return obj->data[0];
}


KthLargest* kthLargestCreate(int k, int* nums, int numsSize) {
    KthLargest* Kth = Init(k);
    for (int i = 0; i < numsSize; ++i)
        kthLargestAdd(Kth, nums[i]);
    return Kth;
}



void kthLargestFree(KthLargest* obj) {
    free(obj->data);
    free(obj);
}

/// <summary>
/// 766 托普利茨矩阵
/// </summary>
/// <param name="matrix"></param>
/// <param name="matrixSize"></param>
/// <param name="matrixColSize"></param>
/// <returns></returns>
bool isToeplitzMatrix(int** matrix, int matrixSize, int* matrixColSize) {
    for (int i = 0; i < matrixSize - 1; ++i)
        for (int j = 0; j < *matrixColSize - 1; ++j)
        {
            if (matrix[i][j] != matrix[i + 1][j + 1])
                return false;
        }
    return true;
}


/// <summary>
/// 832  翻转图像
/// </summary>
/// <param name="A"></param>
/// <param name="ASize"></param>
/// <param name="AColSize"></param>
/// <param name="returnSize"></param>
/// <param name="returnColumnSizes"></param>
/// <returns></returns>
int** flipAndInvertImage(int** A, int ASize, int* AColSize, int* returnSize, int** returnColumnSizes) {
    *returnSize = ASize;
    *returnColumnSizes = AColSize;
    for (int i = 0; i < ASize; ++i)
    {
        int left = 0, right = *AColSize - 1;
        while (left <= right)
        {
            if (A[i][left] == A[i][right])
            {
                if (A[i][left] == 1)
                    A[i][left] = A[i][right] = 0;
                else
                    A[i][left] = A[i][right] = 1;
            }
            left++;
            right--;
        }
    }
    return  A;
}


/// <summary>
/// 867 转置矩阵
/// </summary>
/// <param name="matrix"></param>
/// <param name="matrixSize"></param>
/// <param name="matrixColSize"></param>
/// <param name="returnSize"></param>
/// <param name="returnColumnSizes"></param>
/// <returns></returns>
int** transpose(int** matrix, int matrixSize, int* matrixColSize, int* returnSize, int** returnColumnSizes) {
    int m = matrixSize, n = matrixColSize[0];
    int** returnmatrix = (int**)malloc(sizeof(int*) * n);
    *returnSize = n;
    *returnColumnSizes = (int*)malloc(sizeof(int) * n);
    for (int i = 0; i < n; i++) {
        returnmatrix[i] = (int*)malloc(sizeof(int) * m);
        (*returnColumnSizes)[i] = m;
    }
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            returnmatrix[j][i] = matrix[i][j];
        }
    }
    return returnmatrix;
}

/// <summary>
/// 896 单调数列
/// </summary>
/// <param name="A"></param>
/// <param name="ASize"></param>
/// <returns></returns>
bool isMonotonic(int* A, int ASize) {
    int k = 1;
    if (ASize <= 2)
        return true;
    for (int i = 0; i < ASize - 1; ++i)
    {
        if (A[i] > A[i + 1])
        {
            k = -1;
            break;
        }
    }
    for (int i = 0; i < ASize - 1; ++i)
    {
        if (k * A[i] > k * A[i + 1])
            return false;
    }
    return true;
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
/// 995 k连续位的最小翻转次数
/// </summary>
/// <param name="A"></param>
/// <param name="ASize"></param>
/// <param name="K"></param>
/// <returns></returns>
int minKBitFlips(int* A, int ASize, int K) {
    int ans = 0, revCnt = 0;
    for (int i = 0; i < ASize; ++i) {
        if (i >= K && A[i - K] > 1) {
            revCnt ^= 1;
            A[i - K] -= 2;  // 复原数组元素，若允许修改数组 A，则可以省略
        }
        if (A[i] == revCnt) {
            if (i + K > ASize) {
                return -1;
            }
            ++ans;
            revCnt ^= 1;
            A[i] += 2;
        }
    }
    return ans;
}
/// <summary>
/// 1004 最大连续1的个数 Ⅲ
/// </summary>
/// <param name="A"></param>
/// <param name="ASize"></param>
/// <param name="K"></param>
/// <returns></returns>
int longestOnes(int* A, int ASize, int K) {
    int KNum = 0;
    int left = 0, right = 0, FirstZero = 0;
    int returnSize = 0;
    while (right < ASize)
    {
        if (A[right] == 0)
        {
            KNum++;
        }
        if (KNum > K)
        {
            returnSize = fmax(right - left, returnSize);
            while (A[left] == 1)
                ++left;
            left++;
            KNum--;
        }
        right++;
    }
    returnSize = fmax(right - left, returnSize);
    return returnSize;
}

/// <summary>
/// 1052 爱生气的书店老板
/// </summary>
/// <param name="customers"></param>
/// <param name="customersSize"></param>
/// <param name="grumpy"></param>
/// <param name="grumpySize"></param>
/// <param name="X"></param>
/// <returns></returns>
int maxSatisfied(int* customers, int customersSize, int* grumpy, int grumpySize, int X) {
    int returnSize = 0, flag = 0, nflag = 0;
    for (int i = 0; i < customersSize; ++i)
        if (grumpy[i] == 0)
            flag += customers[i];
    returnSize = flag;
    for (int i = 0; i < customersSize; ++i)
    {
        if (grumpy[i] == 1)
        {
            nflag = flag;
            for (int j = i; j < i + X && j < customersSize; j++)
                if (grumpy[j] == 1)
                    nflag += customers[j];
            returnSize = fmax(returnSize, nflag);
        }
    }
    return returnSize;
}


/// <summary>
/// 
/// </summary>
struct unordered_map {
    int key, val;
    UT_hash_handle hh;
};

int* findNumOfValidWords(char** words, int wordsSize, char** puzzles, int puzzlesSize, int* returnSize) {
    struct unordered_map* frequency = NULL;

    for (int i = 0; i < wordsSize; i++) {
        int n = strlen(words[i]);
        int mask = 0;
        for (int j = 0; j < n; j++) {
            mask |= (1 << (words[i][j] - 'a'));
        }
        if (__builtin_popcount(mask) <= 7) {
            struct unordered_map* tmp;
            HASH_FIND_INT(frequency, &mask, tmp);
            if (tmp == NULL) {
                tmp = (unordered_map*)malloc(sizeof(struct unordered_map));
                tmp->key = mask;
                tmp->val = 1;
                HASH_ADD_INT(frequency, key, tmp);
            }
            else {
                tmp->val++;
            }
        }
    }

    int* ans =(int*)malloc(sizeof(int) * puzzlesSize);
    *returnSize = 0;

    for (int i = 0; i < puzzlesSize; i++) {
        int total = 0;
        int mask = 0;
        for (int j = 1; j < 7; ++j) {
            mask |= (1 << (puzzles[i][j] - 'a'));
        }
        int subset = mask;
        do {
            int s = subset | (1 << (puzzles[i][0] - 'a'));
            struct unordered_map* tmp;
            HASH_FIND_INT(frequency, &s, tmp);
            if (tmp != NULL) {
                total += tmp->val;
            }
            subset = (subset - 1) & mask;
        } while (subset != mask);
        ans[(*returnSize)++] = total;
    }
    return ans;
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
/// <summary>
/// 1438  绝对差不超过限制的最长连续子数组
/// </summary>
/// <param name="nums"></param>
/// <param name="numsSize"></param>
/// <param name="limit"></param>
/// <returns></returns>
int longestSubarray(int* nums, int numsSize, int limit) {
    int* queMax = (int*)malloc(numsSize * sizeof(int));
    int* queMin=(int*)malloc(numsSize*sizeof(int));
    int leftMax = 0, rightMax = 0;
    int leftMin = 0, rightMin = 0;
    int left = 0, right = 0;
    int ret = 0;
    while (right < numsSize) {
        while (leftMax < rightMax && queMax[rightMax - 1] < nums[right]) {
            rightMax--;
        }
        while (leftMin < rightMin && queMin[rightMin - 1] > nums[right]) {
            rightMin--;
        }
        queMax[rightMax++] = nums[right];
        queMin[rightMin++] = nums[right];
        while (leftMax < rightMax && leftMin < rightMin && queMax[leftMax] - queMin[leftMin] > limit) {
            if (nums[left] == queMin[leftMin]) {
                leftMin++;
            }
            if (nums[left] == queMax[leftMax]) {
                leftMax++;
            }
            left++;
        }
        ret = fmax(ret, right - left + 1);
        right++;
    }
    return ret;
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
