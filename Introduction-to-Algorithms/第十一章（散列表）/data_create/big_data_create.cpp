#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <string>

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

// 产生int型数据文件
void fileWtrieNumber( int dataNum)
{
    fstream file;
    file.open("dataNumber.txt", ios::out);

    for (int i = 0; i < dataNum; ++i)
    {
        file << rand() << endl;
    }

    file.close();
}

// 读产生的int型数据文件
void fileReadNumber( int dataNum)
{
    fstream file;
    int data;
    file.open("dataNumber.txt", ios::in);

    for (int i = 0; i < 3; ++i)
    {
        file >> data;
        cout << data << endl;
    }

    file.close();
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

// 读产生的string型数据文件
void fileReadString( int dataNum)
{
    const int num(12); // 定义常数
    char str[num]; // 字符数组
    fstream file;
    file.open("dataString.txt", ios::in);

    for (int i = 0; i < 3; ++i)
    {
        file >> str;
        cout << str << endl;
    }

    file.close();
}

int main()
{
    const int N(10000); // 定义常数

    fileWtrieNumber(N);
    fileWtrieString(N);

    fileReadNumber(N);
    fileReadString(N);

    return 0;
}
