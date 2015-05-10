# 算法导论-第二章-2.1
# 插入排序
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# INSERTION-SORT（A）
# for j <- 2 to length[A]
#     do key <- A[j]
#         Insert A[j] into the sorted sequence A[1...j-1].
#         i <- j-1
#         while i>0 and A[i]>key
#             do A[i+1] <- A[i]
#                 i <- i-1
#         A[i+1] <- key
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 2014. 09. 08
# lichao

import random

# 产生随机数组
# N为数组长度
def gen_rand_n(N):
	A = []
	for i in range(1, N+1):
		A.append(random.randint(1,N*N))
	return A

# 插入排序
# 从A[0]开始
def insertion_sort(A, N):
	for j in range(0, N):
		key = A[j];
		i = j-1;

		while (i>=0) & (A[i]>key):
			A[i+1] = A[i]
			i = i-1

		A[i+1] = key

	return A

# 主函数
N = 10
A = gen_rand_n(N)

print (A)

A = insertion_sort(A, N)

print (A)
