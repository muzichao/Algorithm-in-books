// 算法导论-第八章-8.2
// 计数排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// COUNTING-SORT（A, B, k）
// for i <- 0 to k
//      do C[i] <- 0
// for i <- 0 to length(A)
//      do C[A[i]] <- C[A[i]] +1
// for i <- 1 to k
//      do C[i] <- C[i] + C[i-1]
// for i <- length(A) downto 1
//      do B[C[A[i]]] <- A[i]
//          C[A[i]] <- C[A[i]] -1
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 计数排序的基本思想就是对每一个输入元素x，确定出小于x的元素
// 个数，有了这一信息就可以把x直接放到它在最终输出数组中的位置上
// 适用于输入数据都是0-k之间的整数
// 2014. 10. 17
// lichao

#include <iostream>
#include <stdlib.h>
#include <vector>

using namespace std;

/************************************************************************/
/*函数名：GenRandN
/*功  能：产生随机数组，最大值不超过maxNum
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void GenRandN(int (&A)[SIZE], int maxNum)
{
    srand(5);
    for (int i = 0; i < SIZE; ++i)
        A[i] = rand() % maxNum;
}

/************************************************************************/
/*函数名：CountingSort
/*功  能：计数排序
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void CountingSort(int (&A)[SIZE], int (&B)[SIZE], int k)
{
    vector<int> C(k + 1, 0); // 创建C数组并初始化

    // C的坐标对应A中元素的值，统计A中元素的个数
    for (int i = 0; i < SIZE; i++)
        C[A[i]]++;

    // C中计数累加，此时A[i]对应C中的A[i]处
    // C[i]包含等于i的元素个数
    for (int i = 1; i <= k; ++i)
        C[i] += C[i - 1];

    // 而C[A[i]]存的元素即为A[i]在B中的正确位置
    // 数组下标应从0开始，因此用C[A[j]]减去1
    // C[i]包含小于等于i的元素个数
    for (int i = SIZE - 1; i >= 0; i--)
    {
        B[C[A[i]] - 1] = A[i];
        C[A[i]] = C[A[i]] - 1; // 有相同元素的话，相同元素依次前移
    }
}

/************************************************************************/
/*函数名：PrintfArray
/*功  能：输出数组
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void PrintfArray(int (&A)[SIZE])
{
    for (int i = 0; i < SIZE; ++i)
        cout << A[i] << " ";

    cout << endl;
}

/************************************************************************/
/*函数名：IsOrder()
/*功  能：判断函数是否有序
/*返回值：返回0或1
/************************************************************************/
template<size_t SIZE>
bool IsOrder(int (&A)[SIZE])
{
    if (1 == SIZE)
        return true;

    int i = 1;
    while (A[i - 1] <= A[i] && i < SIZE)
        i++;

    if (SIZE == i)
        return true;
    else
        return 0;
}

const int N(200000); // 定义常数
const int maxNum(1000000); // 定义常数

int dataA[N] = {0}; // 定义数组
int dataB[N] = {0}; // 定义数组

int main()
{
    GenRandN(dataA, maxNum); // 产生随机数组

    CountingSort(dataA, dataB, maxNum); // 计数排序

    // 输出排序前数组
    // PrintfArray(dataA);

    // 输出排序后数组
    // PrintfArray(dataB);

    // 判断排序是否准确
    cout << IsOrder(dataB) << endl;

    return 0;
}
