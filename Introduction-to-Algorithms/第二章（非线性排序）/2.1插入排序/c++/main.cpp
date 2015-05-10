
// 算法导论-第二章-2.1
// 插入排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// INSERTION-SORT（A）
// for j <- 2 to length[A]
//     do key <- A[j]
//         Insert A[j] into the sorted sequence A[1...j-1].
//         i <- j-1
//         while i>0 and A[i]>key
//             do A[i+1] <- A[i]
//                 i <- i-1
//         A[i+1] <- key
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 2014. 09. 08
// lichao

#include <iostream>
#include <stdlib.h>

using namespace std;

// 产生随机数组
template<size_t SIZE>
void gen_rand_n(int (&A)[SIZE])
{
	srand(5);
	for (int i = 0; i < SIZE; ++i)
	{
		A[i] = rand();
	}
}

// 插入排序
template<size_t SIZE>
void insertion_sort(int (&A)[SIZE])
{
	int key = 0;
	int j = 0;

	for (int i = 1; i < SIZE; ++i)
	{
		key = A[i];
		j = i - 1;
		while((j >= 0) && (A[j] > key))
		{
		    A[j+1] = A[j];
		    j = j-1;
		}
		A[j+1] = key;
	}
}

int main()
{	
	const int N(100); // 定义数组长度

	int A[N] = {0}; // 定义数组
	gen_rand_n(A); // 产生随机数组

	// for (int i = 0; i < N; ++i)
	// {
	// 	cout << A[i] << endl;
	// }

	insertion_sort(A);

	for (int i = 0; i < N; ++i)
	{
		cout << A[i] << endl;
	}

	return 0;
}


