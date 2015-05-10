// 编程之美 2.4
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 1:N的所有数字中包含数字1的个数
// 如：1:10，包含2个1
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路：1. 从1:N遍历一遍，找出每个数中的1的个数
// 2. 直接根据N计算1的个数
// f(N) = 个位上1的个数 + 十位上1的个数 + ...
// 假设N = abcde
// 1.如果百位上的数字(c)为0，则百位出现1的个数为：
// 更高位数字(ab)乘以当前位数，即(ab)× 100
// 2.如果百位上的数字(c)为1，则百位出现1的个数为：
// 更高位数字(ab)乘以当前位数，即(ab)× 100，加上
// 低位数字(cde)+ 1，即(ab)× 100 + (cde)+ 1
// 3.如果百位上的数字(c)大于1，则百位出现1的个数为：
// 更高位数字加1(ab+1)乘以当前位数，即(ab+1)×100
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
#include <iostream>

using namespace std;

// 遍历所有数，找出每个数中1的个数
int coutNumOne1(unsigned int N)
{
    int num = 0;
    int a = 0;

    for (int i = 1; i <= N; ++i)
    {
        a = i;
        while(a)
        {
            if (a%10 == 1)
            {
                num++;
            }
            a /= 10;
        }
    }
    return num;
}

// 直接根据N计算1的个数
int coutNumOne2(unsigned int N)
{
    int num = 0;
    unsigned int currentNum = 0; // 当前位数
    unsigned int factor = 1; // 因数
    unsigned int highNum = 0; // 高位数
    unsigned int lowNum = 0; // 低位数

    while(N / factor > 0)
    {
        currentNum = (N / factor) % 10;
        highNum = N / (factor * 10);
        lowNum = N - (N / factor) * factor;

        switch(currentNum)
        {
            case 0:
                num += highNum * factor;
                break;
            case 1:
                num += highNum * factor + lowNum + 1;
                break;
            default:
                num += (highNum + 1) * factor;
                break;
        }

        factor *= 10;
    }
    return num;
}

int main()
{
    unsigned int N = 12345;
    int num = 0;

    num = coutNumOne1(N);
    cout << "num = " << num << endl;

    num = coutNumOne2(N);
    cout << "num = " << num << endl;

    return 0;
}
