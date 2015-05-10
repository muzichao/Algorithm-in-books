#include "hashtable.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <fstream>

using namespace std;

// 产生随机字符串
template<size_t Len>
void gen_rand_s(char (&str)[Len])
{
    const int sizeChar = 62;
    char allChar[sizeChar + 1] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

    for (int i = 0; i < Len-1; ++i)
    {
        str[i] = allChar[rand() % sizeChar];
    }
    str[Len-1] = '\0';
}

// 产生string型数据文件
void fileWtrieString( int dataNum)
{
    const int num(12); // 定义常数
    char str[num]; // 字符数组
    fstream file;
    file.open("dataString.txt", ios::out);

    for (int i = 0; i < dataNum; ++i)
    {
        gen_rand_s(str);
        file << str << endl;
    }

    file.close();
}


const int MAXDATAN = 5000000, MAXQUERYN = 5000000; // 存储数据量和查询数据量

int main()
{
    fileWtrieString(MAXDATAN); // 产生字符串数组文件

    // 读文件参数
    hashNodeType str;
    fstream file;

    hashtable myHashTable(5614657); // 定义哈希表

    int iSucceedQuery = 0, iFailedQuery = 0; // 标记成功查询和失败查询次数


    // 插入哈希表测试
    clock_t startTime, endTime;
    startTime = clock(); // 开始计时
    file.open("dataString.txt", ios::in);
    for (int i = 0; i < MAXDATAN; ++i)
    {
        file >> str;
        myHashTable.InsertHashTable(str); // 插入哈希表
    }
    file.close();
    endTime = clock(); // 结束计时
    cout<< "Run time of insert: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    // 查询哈希表测试
    startTime = clock(); // 开始计时
    file.open("dataString.txt", ios::in);
    for (int i = 0; i < MAXDATAN; ++i)
    {
        file >> str;
        if (myHashTable.FindHashTable(str)) // 查询哈希表
        {
            iSucceedQuery++;
        }
        else
        {
            iFailedQuery++;
        }

    }
    file.close();
    endTime = clock(); // 结束计时
    cout<< "Run time of query: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;

    cout << "query number of succeed: " << iSucceedQuery << endl;
    cout << "query number of failed: " << iFailedQuery << endl;

    myHashTable.ShowNodeLinkSize();
    return 0;
}

