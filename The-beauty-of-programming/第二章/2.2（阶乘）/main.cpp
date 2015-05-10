// 编程之美 2.2
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 1. 给定整数N，判断N！末尾有多少个0
// 2. 求N！的二进制表示中最低位1的位置
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路：1. 即求N！中含有质因数5的个数
// 2. 即求N！中含有质因数2的个数
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <iostream>

using namespace std;

// 1:N中质因数5的个数
int coutZeroOfFactorialN1(unsigned int N, unsigned int primNum)
{
   int a = 0;
    int num = 0;

    for (int i = primNum; i <= N; i = i+primNum)
    {
        a = i;
        while(a>0 & a%primNum == 0)
        {
            a = a/primNum;
            // cout << "i = " << i << endl;
            // cout << "a = " << a << endl;
            num++;
        }
    }
    return num;
}

// N/primNum + N/primNum^2 + N/primNum^3 + ...
int coutZeroOfFactorialN2(unsigned int N, unsigned int primNum)
{
    int num = 0;
    int a = primNum;

    while(a <= N)
    {
        num += N/a;
        a *= primNum;
    }
    return num;
}

int main()
{
    unsigned int N = 5511;
    unsigned int primNum = 11;

    int num = 0;

    num = coutZeroOfFactorialN1(N, primNum);
    cout << "num = " << num << endl;

    primNum = 11;
    num = coutZeroOfFactorialN2(N, primNum);
    cout << "num = " << num << endl;

    return 0;
}
