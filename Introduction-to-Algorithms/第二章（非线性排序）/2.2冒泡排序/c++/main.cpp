// 算法导论-第二章-2.2
// 冒泡排序
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 冒泡排序就是把小的元素往前调或者把大的元素往后调
// 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// BUBBLE-SORT（A）
// bubble_sort(A)
// {
//    for i = 1 to length[A]
//    {
//        for j = length[A] to i+1
//        {
//            if A[j] < A[j-1]
//            {
//                 exchane A[j] and A[j-1];
//            }
//        }
//    }
// }
// %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// 2014. 09. 09
// lichao

#include <iostream>
#include <stdlib.h>

using namespace std;

// #include <stdlib.h>
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

// 数组冒泡排序
template<size_t SIZE>
void bubble_sort(int (&A)[SIZE])
{
  int temp = 0;

  for (int i = 0; i < SIZE; ++i)
  {
    for (int j = SIZE-1; j > i+1; --j)
    {   
      if (A[j] < A[j-1])
      {
        temp = A[j];
        A[j] = A[j-1];
        A[j-1] = temp; 
      }
    }
  }
}

int main()
{
  const int N(30); // 定义数组长度

  int A[N] = {0}; // 定义数组

  gen_rand_n(A); // 产生随机数组

  bubble_sort(A); // 数组冒泡排序

  for (int i = 0; i < N; ++i)
  {
    cout << A[i] << endl;
  }

  return 0;
}
