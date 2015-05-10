#include "CountingSortCPU.h"
#include <iostream>
#include <vector>

using namespace std;

/************************************************************************/
/*函数名：CountingSort
/*功  能：计数排序
/*返回值：无
/************************************************************************/
void CountingSort(int *A, int *B, const int SIZE, const int k)
{
	vector<int> C(k + 1, 0); // 创建C数组并初始化

	// C的坐标对应A中元素的值，统计A中元素的个数
	for (int i = 0; i < SIZE; i++)
		C[A[i]]++;

	// C中计数累加，此时A[i]对应C中的A[i]处
	// C[i]包含等于i的元素个数
	for (int i = 1; i <= k; ++i)
		C[i] += C[i - 1];

	// 而C[A[i]]存的元素即为A[i]在B中的正确位置
	// 数组下标应从0开始，因此用C[A[j]]减去1
	// C[i]包含小于等于i的元素个数
	for (int i = SIZE - 1; i >= 0; i--)
	{
		B[C[A[i]] - 1] = A[i];
		C[A[i]]--; // 有相同元素的话，相同元素依次前移
	}
}