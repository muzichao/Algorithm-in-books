// 编程之美 2.7
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 求两个正整数的最大公约数
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路1：辗转相除法
// 取k = x/y, b = x%y, x = ky + b
// 一个数能同时整除x和y，则必能同时整除b和y
// 所以：f(x, y) = f(y, x % y)(x >= y > 0)
// 思路2：更相减损法
// x > y : f(x, y) = f(x-y, y)
// x < y : f(x, y) = f(y, x)
// 思路3：辗转相除法结合更相减损法
// 如果x，y为偶数：f(x, y) = 2 * f(x >> 1, y >> 1)
// 如果x为偶数，y为奇数：f(x, y) = f(x >> 1, y)
// 如果x为奇数，y为偶数：f(x, y) = f(x, y >> 1)
// 如果x，y为奇数：f(x, y) = f(y, x - y) (x-y 为偶数)
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <iostream>

using namespace std;

// 辗转相除法（取模，除法运算复杂度高）
int greatestCommonDivisor_del(int x, int y)
{
    return (!y) ? x : greatestCommonDivisor_del(y, x % y);
}

// 更相减损法（迭代次数多）
int greatestCommonDivisor_sub(int x, int y)
{
    if (x < y)
    {
        return greatestCommonDivisor_sub(y, x);
    }

    if (y == 0)
    {
        return x;
    }
    else
    {
        return greatestCommonDivisor_sub(x - y, y);
    }
}

// 辗转相除法结合更相减损法
int greatestCommonDivisor_sub_del(int x, int y)
{
    if (x < y)
    {
        return greatestCommonDivisor_sub_del(y, x);
    }

    if (y == 0)
    {
        return x;
    }
    else
    {
        if (x & 1 == 0) // 如果x为偶数
        {
            if (y & 1 == 0) // 如果y为偶数
            {
                return 2 * greatestCommonDivisor_sub_del(x >> 1, y >> 1);
            }
            else // 如果y为奇数
            {
                return greatestCommonDivisor_sub_del(x >> 1, y);
            }
        }
        else // 如果x为奇数
        {
            if(y & 1 == 0) // 如果y为偶数
            {
                return greatestCommonDivisor_sub_del(x, y >> 1);
            }
            else // 如果y为奇数
            {
                return greatestCommonDivisor_sub_del(y, x - y);
            }
        }
    }
}

int main()
{
    int N = 12 * 770;
    int M = 42 * 770;

    int gcd_del = 0;
    gcd_del = greatestCommonDivisor_del(N, M);
    cout << gcd_del << endl;

    int gcd_sub = 0;
    gcd_sub = greatestCommonDivisor_sub(N, M);
    cout << gcd_sub << endl;

    int gcd_sub_del = 0;
    gcd_sub_del = greatestCommonDivisor_sub_del(N, M);
    cout << gcd_sub_del << endl;

    return 0;
}
