#include "GenRandN.h"
#include <iostream>

// MSVC中RAND_MAX通常为0x7fff，即32767，而Linux平台下GCC中RAND_MAX通常会远远大于这个值
/************************************************************************/
/*函数名：GenRandN
/*功  能：产生随机数组，最大值不超过maxNum
/*返回值：无
/************************************************************************/
void GenRandN(int *A, const int SIZE, const int maxNum)
{
	srand(5);
	for (int i = 0; i < SIZE; ++i)
		A[i] = (rand() * rand()) % maxNum;
}