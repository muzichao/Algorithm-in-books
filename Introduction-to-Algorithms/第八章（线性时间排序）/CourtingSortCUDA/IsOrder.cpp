#include "IsOrder.h"

/************************************************************************/
/*函数名：IsOrder()
/*功  能：判断函数是否有序
/*返回值：返回0或1
/************************************************************************/
bool IsOrder(int *A, const int SIZE)
{
	if (1 == SIZE)
		return true;

	int i = 1;
	while (A[i - 1] <= A[i] && i < SIZE)
		i++;

	return SIZE == i ? true : false;
}