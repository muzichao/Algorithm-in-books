// 编程之美 2.8
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 任意给定一个正整数N，求一个最小的正整数M(M>1)，使N×M的十
// 进制式里只含有0和1
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 思路：
// 1.从1开始遍历，直到找到合适的M
// 2.从1,10,11,100,101,110,111开始遍历，找到能被N整除的N*M
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

#include <iostream>
#include <time.h>

using namespace std;

typedef unsigned long long int MyCustomType;

// 判断一个正整数的十进制表示里只有0和1
bool onlyZeroAndOneInDecimal(MyCustomType decimalNum)
{
    // 末位是0或者1并且大于0的时候消去最后一位
    while (decimalNum % 10 < 2 && decimalNum > 0)
    {
        decimalNum /= 10;
    }

    // 如果最后的值是0或者1则表示满足条件
    return decimalNum == 0 ? true : false;

}

// 用二进制数表示十进制中只有0和1的数字
MyCustomType binaryToDecimal(int binaryNUM)
{
    MyCustomType decimalNum = 0;
    MyCustomType times = 1;

    while (binaryNUM)
    {
        decimalNum += times * (binaryNUM % 2);
        times *= 10;
        binaryNUM /= 2;
    }

    return decimalNum;
}

// 1.从1开始遍历，直到找到合适的M
MyCustomType calculateMUseMethonOne(MyCustomType N)
{
    MyCustomType M = 1;
    while (!onlyZeroAndOneInDecimal(N * M))
    {
        M++;
    }

    return M;
}

// 2.从1,10,11,100,101,110,111开始遍历，找到能被N整除的N*M
MyCustomType calculateMUseMethonTwo(MyCustomType N)
{
    int binaryNUM = 1;
    MyCustomType NM = binaryToDecimal(binaryNUM);

    while (NM / N * N != NM)
    {
        binaryNUM++;
        NM = binaryToDecimal(binaryNUM);
    }

    return NM / N;
}

int main()
{
    MyCustomType N = 72;
    MyCustomType M = 0;
    clock_t start, end;

    start = clock();
    M = calculateMUseMethonOne(N);
    cout << "Method One: " << "M = " << M << " NM = " << N * M << endl;
    end = clock();
    cout << "Run time: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;


    start = clock();
    M = calculateMUseMethonTwo(N);
    cout << "Method Two: " << "M = " << M << " NM = " << N * M << endl;
    end = clock();
    cout << "Run time: " << (double)(end - start) / CLOCKS_PER_SEC << "S" << endl;

    return 0;
}

