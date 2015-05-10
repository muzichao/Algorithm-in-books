#include "hashtable.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

// 产生[0, iMaxNum)范围内随机数组
// srand()用来设置rand()产生随机数时的随机数种子。
// 如果每次seed都设相同值，rand()所产生的随机数值每次就会一样。
template<size_t SIZE>
void gen_rand_n(int (&A)[SIZE], int iMaxNum)
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < SIZE; ++i)
    {
        A[i] = (rand() * rand()) % iMaxNum;
    }
}

const int MAXDATAN = 5000000, MAXQUERYN = 5000000; // 存储数据量和查询数据量
int data[MAXDATAN], query[MAXQUERYN]; // 大数组存储在静态数据区，不要存在栈中

int main()
{
    const int MAXNUM = MAXDATAN * 4; // 决定产生存储数据范围
    const int MAXQUERYNUM = MAXQUERYN * 4; // 决定产生查询数据范围

    gen_rand_n(data, MAXNUM); // 产生存储数组
    gen_rand_n(query, MAXQUERYNUM); // 产生查询数组

    hashtable myHashTable(MAXDATAN + 123); // 定义哈希表

    int iSucceedQuery = 0, iFailedQuery = 0; // 标记成功查询和失败查询次数

    clock_t startTime, endTime;
    startTime = clock(); // 开始计时
    for (int i = 0; i < MAXDATAN; ++i)
    {
        myHashTable.InsertHashTable(data[i]); // 插入哈希表
    }
    endTime = clock(); // 结束计时
    cout<< "Run time of insert: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    startTime = clock(); // 开始计时
    for (int i = 0; i < MAXDATAN; ++i)
    {
        if (myHashTable.FindHashTable(query[i])) // 查询哈希表
        {
            iSucceedQuery++;
        }
        else
        {
            iFailedQuery++;
        }

    }
    endTime = clock(); // 结束计时
    cout<< "Run time of query: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    cout << "query number of succeed: " << iSucceedQuery << endl;
    cout << "query number of failed: " << iFailedQuery << endl;

    myHashTable.ShowNodeLinkSize();
    cout << myHashTable.SizeHashTable() << endl;

    return 0;
}

