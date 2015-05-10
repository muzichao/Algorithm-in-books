#ifndef COUNTINGSORTCUDA_H
#define COUNTINGSORTCUDA_H




/************************************************************************/
/*函数名：CountingSort
/*功  能：CUDA计数排序，输入A，输出B
/*返回值：无
/************************************************************************/
void CountingSortCUDA(int *A, int *B, const int SIZE, const int k);

#endif // COUNTINGSORTCUDA_H
