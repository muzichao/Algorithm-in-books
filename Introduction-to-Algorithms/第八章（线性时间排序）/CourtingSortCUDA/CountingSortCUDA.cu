#include "CountingSortCUDA.h"
#include "MyCuda.h"
#include <iostream>
#include <vector>

using namespace std;

/************************************************************************/
/*函数名：CountingSortKernelOne
/*功  能：计数排序第一步，C[i]为A中元素i的个数
/*返回值：无
/************************************************************************/
__global__ void CountingSortKernelOne(int *A, int *C, int iSize)
{
	// 坐标索引
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标

	if (x_id < iSize)
	{
		int iIdx = A[x_id];
		atomicAdd(&C[iIdx], 1);
	}
}

/************************************************************************/
/*函数名：CountingSortKernelTwo
/*功  能：计数排序第二步核函数，进行一次规约
/*返回值：无
/************************************************************************/
__global__ void CountingSortKernelTwo(int *C, int k, int iSize)
{
	// 坐标索引
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标

	x_id++;

	if (x_id <= k)
	{
		int iRe = x_id & (iSize - 1);
		if (0 == iRe)
			iRe = iSize;

		if (iRe > (iSize >> 1))
		{
			x_id--;
			C[x_id] = C[x_id] + C[x_id + (iSize >> 1) - iRe];
		}
	}
}

/************************************************************************/
/*函数名：CountingSortTwo
/*功  能：计数排序第二步，对C数组进行累积和规约
/*返回值：无
/************************************************************************/
void CountingSortTwo(dim3 dimGridK, dim3 dimBlockK, int *devC, int k)
{
	int iSize = 1;
	while (iSize <= k)
	{
		iSize = iSize << 1;
		CountingSortKernelTwo<<<dimGridK, dimBlockK>>>(devC, k, iSize);
	}
}

/************************************************************************/
/*函数名：CountingSortKernelThree
/*功  能：计数排序第三步，利用C数组和下标进行最终排序
/*返回值：无
/************************************************************************/
__global__ void CountingSortKernelThree(int *B, int *C, int k)
{
	// 坐标索引
	int x_id = blockDim.x * blockIdx.x + threadIdx.x; // 列坐标

	if (x_id <= k)
	{
		int iStart = 0;
		if (0 != x_id)
			iStart = C[x_id - 1];

		for (int i = iStart; i < C[x_id]; i++)
		{
			B[i] = x_id;
		}
	}
}

/************************************************************************/
/*函数名：CountingSort
/*功  能：CUDA计数排序，输入A，输出B
/*返回值：无
/************************************************************************/
void CountingSortCUDA(int *A, int *B, const int SIZE, const int k)
{
	vector<int> C(k + 1, 0); // 创建C数组并初始化

	int *devA;
	int *devB;
	int *devC;

	cudaMalloc((void**)&devA, sizeof(int) * SIZE);
	cudaMalloc((void**)&devB, sizeof(int) * SIZE);
	cudaMalloc((void**)&devC, sizeof(int) * (k + 1));

	cudaMemcpy(devA, A, sizeof(int) * SIZE, cudaMemcpyHostToDevice);
	cudaMemset(devB, 0, sizeof(int) * SIZE);
	cudaMemset(devC, 0, sizeof(int) * (k + 1));

	dim3 dimBlock(BLOCK_SIZE);
	dim3 dimGrid((SIZE + BLOCK_SIZE - 1) / BLOCK_SIZE);
	dim3 dimGridK((k + BLOCK_SIZE - 1) / BLOCK_SIZE);

	// C的坐标对应A中元素的值，统计A中元素的个数
	CountingSortKernelOne<<<dimGrid, dimBlock>>>(devA, devC, SIZE);

	// C中计数累加，此时A[i]对应C中的A[i]处
	// C[i]包含等于i的元素个数
	CountingSortTwo(dimGridK, dimBlock, devC, k + 1);


	// 而C[A[i]]存的元素即为A[i]在B中的正确位置
	// 数组下标应从0开始，因此用C[A[j]]减去1
	// C[i]包含小于等于i的元素个数
	CountingSortKernelThree<<<dimGridK, dimBlock>>>(devB, devC, k);

	cudaMemcpy(B, devB, sizeof(int) * SIZE, cudaMemcpyDeviceToHost);

	cudaFree(devA);
	cudaFree(devB);
	cudaFree(devC);
}