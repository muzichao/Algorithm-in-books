// 编程之美 2.1
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 对于一个字节（8bit）的无字符型整数，求其二进制中'1'的个数
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路：对某个数除2取余，如果等于1，则表明二进制表示中最后
// 一位为1，循环操作，可以读取出1的个数。
//
// 对某个数除2，也就是向右移位一个
// 判断某个数二进制的最后一位是否为1，只需与0x01进行与操作
//
// a&(a-1):相当于将二进制中最后一个1置0
#include <iostream>

using namespace std;

// 利用除法和取余操作
int coutNumOneMethod1(unsigned char a)
{
	int num = 0;

	while(a)
	{
		if (a%2 == 1)
		{
			num++;
		}
		a = a/2;
	}
	return num;
}

// 利用移位和与操作
int coutNumOneMethod2(unsigned char a)
{
	int num = 0;

	while(a)
	{
	    num += a & 0x01;
	    a >>= 1;
	}
	return num;
}

// a&(a-1):相当于将二进制中最后一个1置0
int coutNumOneMethod3(unsigned char a)
{
    int num = 0;

    while(a)
    {
        a &= (a-1);
        num++;
    }
    return num;
}

int main()
{
	unsigned char a = 155;

	// 利用除法和取余
	int num1 = 0;
	num1 = coutNumOneMethod1(a);
	cout << num1 << endl;

	// 利用移位和与操作
	a = 155;
	int num2 = 0;
	num2 = coutNumOneMethod2(a);
	cout << num2 << endl;

    // 利用移位和与操作
    a = 155;
    int num3 = 0;
    num3 = coutNumOneMethod3(a);
    cout << num3 << endl;

	return 0;
}
