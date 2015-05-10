# 算法导论-第二章-2.2
# 冒泡排序
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 冒泡排序就是把小的元素往前调或者把大的元素往后调
# 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# BUBBLE-SORT（A）
# bubble_sort(A)
# {
#    for i = 1 to length[A]
#    {
#        for j = length[A] to i+1
#        {
#            if A[j] < A[j-1]
#            {
#                 exchane A[j] and A[j-1];
#            }
#        }
#    }
# }
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 2014. 09. 09
# lichao

import random

#import random
# 产生随机数组
# N为数组长度
def gen_rand_n(N):
  A = []
  for i in range(1, N+1):
    A.append(random.randint(1,10*N))
  return A

# 冒泡排序
# 从A[0]开始
def bubbl_sort(A, N):
  temp = 0;
  for i in range(0, N):
      for j in range(N-1, i, -1):
        if A[j] < A[j-1]:
          temp = A[j]
          A[j] = A[j-1]
          A[j-1] = temp

  return A

# 主函数
N = 10
A = gen_rand_n(N)

print (A)

A = bubbl_sort(A, N)

print (A)
