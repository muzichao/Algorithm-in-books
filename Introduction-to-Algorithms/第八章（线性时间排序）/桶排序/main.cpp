// 算法导论-第八章-8.2
// 桶排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// A>0,A<1
// BUCKET-SORT（A）
// n <- length[A]
// for i <- 1 to n
//      do insert A[i] to B[int(n*A([i])]
// for i <- 0 to n-1
//      do sort list B[i] with insertion sort
// concatenate the lists B[0], B[1], ..., B[n-1]together
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 把［0, 1)区间划分成n个相同大小的自取间，或称为桶
// 把n个数据分别放入对应的桶中
// 对各桶中元素进行排序
// 按次序把各桶中元素取出来
// 适用于输入近似符合均匀分布
// 2014. 10. 18
// lichao

#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <time.h>

using namespace std;

struct Node
{
    int value; // 值
    Node *next; // 指向Node的指针

    Node (int val) // 析构函数
    {
        this->value = val;
        this->next = NULL;
    }
};

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

/************************************************************************/
/*函数名：BucketSort()
/*功  能：桶排序
/*返回值：无
/************************************************************************/
template<size_t SIZE>
bool BucketSort(int (&A)[SIZE])
{
    Node **pNode = (Node **)malloc(sizeof(Node *) * 256);
    if (NULL == pNode)
        return false;

    memset(pNode, 0, sizeof(Node *) * 256);

    int numWithShift = 0;
    Node *p = NULL;
    Node *pLast = NULL;
    Node *pNewNode = NULL;

    for (int i = 0; i < SIZE; ++i)
    {
        numWithShift = A[i] >> 24;
        p = pNode[numWithShift];

        pNewNode = new Node(A[i]);
        if (NULL == pNewNode)
            return false;

        if (NULL == p) // 为空，插入
        {
            pNode[numWithShift] = pNewNode;
        }
        else if (A[i] <= p->value) // 不为空但小于等于第一个节点，插入
        {
            pNode[numWithShift] = pNewNode;
            pNewNode->next = p;
        }
        else // 不为空，且大于第一个节点
        {
            while (NULL != p->next)
            {
                if (A[i] > p->next->value)
                    p = p->next;
                else
                    break;
            }
            pNewNode->next = p->next;
            p->next = pNewNode;
        }
    }

    for (int i = 0, k = 0; i < 256; ++i)
    {
        p = pNode[i];

        while (NULL != p)
        {
            A[k++] = p->value;
            p = p->next;
        }
    }

    return true;
}

const int N(200000); // 定义常数
const int maxNum(0x7FFFFFFF); // 定义常数
int dataA[N] = {0}; // 定义数组


int main()
{
    GenRandN(dataA, maxNum); // 产生随机数组
    // 输出排序前数组
    // PrintfArray(dataA);

    clock_t startTime, endTime;

    startTime = clock();
    BucketSort(dataA); // 计数排序
    endTime = clock();
    cout << "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    // 输出排序后数组
    // PrintfArray(dataA);

    // 判断排序是否准确
    cout << IsOrder(dataA) << endl;

    return 0;
}
