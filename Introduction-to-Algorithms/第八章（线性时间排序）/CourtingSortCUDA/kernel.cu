#include <iostream>
#include <vector>
#include <time.h>
#include <fstream>

#include "MyCuda.h"
#include "GenRandN.h"
#include "CountingSortCPU.h"
#include "IsOrder.h"
#include "CountingSortCUDA.h"

using namespace std;


/************************************************************************/
/*函数名：PrintfArray
/*功  能：输出数组
/*返回值：无
/************************************************************************/
void PrintfArray(int *A, const int SIZE)
{
	for (int i = 0; i < SIZE; ++i)
		cout << A[i] << " ";

	cout << endl;
}



const int N(80000000); // 定义常数
const int maxNum(10000000); // 定义常数

int main()
{
	vector<int> dataA(N, 0);
	vector<int> dataCPU(N, 0);
	vector<int> dataCUDA(N, 0);

	GenRandN(&dataA[0], N, maxNum); // 产生随机数组

	clock_t startTime, endTime;
	startTime = clock();

	CountingSort(&dataA[0], &dataCPU[0], N, maxNum); // 计数排序

	endTime = clock();
	cout<< "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;


	startTime = clock();

	CountingSortCUDA(&dataA[0], &dataCUDA[0], N, maxNum); // 计数排序

	endTime = clock();
	cout<< "Run time: " << (double)(endTime - startTime) / CLOCKS_PER_SEC << "S" << endl;


	// 判断排序是否准确
	cout << IsOrder(&dataCPU[0], N) << endl;
	cout << IsOrder(&dataCUDA[0], N) << endl;
	cout << dataCPU[N-1] << " " << dataCUDA[N-1] << endl;

	return 0;
}

