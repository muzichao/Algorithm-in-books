// 算法导论-第八章-8.2
// 基数排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// RADIX-SORT（A, d）
// for i <- 1 to d
//      do use a stable sort to sort array A on digit i
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 先取个位数字，按照个位数字进行计数排序
// 取十位数字，按十位数字进行计数排序
// 取百位数字，按百位数字进行计数排序
// 。。。。。。。
// 优化后的方法
// 由于取个位数字要反复的继续除法和取余运算，效率不高
// 可以考虑每次取二进制的几位，就可以用移位和与运算
// 取的位数较少，循环次数增加，位数较多，中间数组大
// 2014. 10. 18
// lichao

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <time.h>


using namespace std;

/************************************************************************/
/*函数名：PrintfArray
/*功  能：输出数组
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void PrintfArray(int (&A)[SIZE])
{
    for (int i = 0; i < SIZE; ++i)
        cout << hex << A[i] << " ";

    cout << endl;
}

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
        A[i] = (rand() * rand()) % maxNum;
}

/************************************************************************/
/*函数名：GetNumberDigit
/*功  能：获取数组中每个数字的第i位数字
/*返回值：无
/************************************************************************/
template<size_t SIZE>
bool GetNumberDigit(int (&A)[SIZE], int (&B)[SIZE], unsigned int digit)
{
    unsigned int shift = 8 * (digit - 1);

    if (shift % 4 != 0  | shift > 24)
        return 0;

    for (int i = 0; i < SIZE; ++i)
        B[i] = (A[i] >> shift) & 0xFF;

    return 1;
}

/************************************************************************/
/*函数名：CountingSort
/*功  能：计数排序
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void CountingSort(int (&A)[SIZE], int (&B)[SIZE], int (&C)[SIZE])
{
    vector<int> D(256, 0); // 创建D数组并初始化

    // D的坐标对应A中元素的值，统计A中元素的个数
    for (int i = 0; i < SIZE; i++)
        D[C[i]]++;

    // D中计数累加，此时C[i]对应D中的A[i]处
    // D[i]包含等于i的元素个数
    for (int i = 1; i < 256; ++i)
        D[i] += D[i - 1];

    // 而D[A[i]]存的元素即为A[i]在B中的正确位置
    // 数组下标应从0开始，因此用D[A[j]]减去1
    // D[i]包含小于等于i的元素个数
    for (int i = SIZE - 1; i >= 0; i--)
    {
        B[D[C[i]] - 1] = A[i];
        D[C[i]] = D[C[i]] - 1; // 有相同元素的话，相同元素依次前移
    }
}

/************************************************************************/
/*函数名：RadixSort
/*功  能：基数排序
/*返回值：无
/************************************************************************/
template<size_t SIZE>
void RadixSort(int (&A)[SIZE], int (&B)[SIZE])
{
    int C[SIZE] = {0}; // 保存中间变量
    int D[SIZE] = {0}; // 保存中间变量

    for (int i = 0; i < SIZE; ++i)
        B[i] = A[i];

    for (int i = 1; i < 5; ++i)
    {
        if (i & 0x01 == 1)
        {
            GetNumberDigit(B, C, i);
            CountingSort(B, D, C);
        }
        else
        {
            GetNumberDigit(D, C, i);
            CountingSort(D, B, C);
        }
    }
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
        return false;
}

const int N(200000); // 定义常数
const int maxNum(0x7FFFFFFF); // 定义常数
int dataA[N] = {0}; // 定义数组
int dataB[N] = {0}; // 定义数组

int main()
{
    GenRandN(dataA, maxNum); // 产生随机数组

    clock_t startTime, endTime;

    startTime = clock();
    RadixSort(dataA, dataB); // 计数排序
    endTime = clock();
    cout<< "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;


    // 输出排序前数组
    // PrintfArray(dataA);

    // 输出排序后数组
    // PrintfArray(dataB);

    // 判断排序是否准确
    cout << IsOrder(dataB) << endl;

    return 0;
}
