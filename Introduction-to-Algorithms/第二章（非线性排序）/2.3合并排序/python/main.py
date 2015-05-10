# 算法导论-第二章-2.3
# 合并排序排序
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 合并排序是一张分治法
# 分解：将n个元素分成各含n/2个原始的子序列
# 解决：用合并排序法对两个子序列递归的排序
# 合并：合并两个已经排好序的子序列以得到一个排好序的序列
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 假设A[p..q]和A[q+1,r]都已排好序

# MERGE（A, p, q, r）
#     n1 <- q-p+1
#     n2 <- r-q
#     create arrays L[1..n1+1] and R[1..n2+1]
#     for i <- 1 to n1
#         do L[i] <- A[p+i-1]
#     for j <- 1 to n2
#         do R[i] <- A[q+j]
#     L[n1+1] <- inf
#     R[n2+1] <- inf
#     i <- 1
#     j <- 1
#     for k <- p to r
#         do if L[i] <= R[j]
#             then A[k] <- L[i]
#                 i <- i+1
#             else A[k] <- R[j]
#                 j <- j+1

# MERGE-SORT(A, p, r)
#     if p < r
#         then q <- fix(（p+r）/2)
#           MERGE-SORT(A, p, r)
#           MERGE-SORT(A, q+1, r)
#           MERGE(A, p, q, r)
# %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
# 2014. 09. 10
# lichao

import random

# import random
# 产生随机数组
# N为数组长度
def gen_rand_n(N):
    A = []
    for i in range(1, N+1):
        A.append(random.randint(1,10*N))
    return A

# 合并排序子函数
# 从A[0]开始
def merge(A, p, q, r):
    n1 = q - p + 1
    n2 = r - q
    L = []
    R = []

    for i in range(0, n1):
        L.append(A[p+i])

    for i in range(0, n2):
        R.append(A[q+1+i])

    L.append(float("inf"))
    R.append(float("inf"))

    i = 0;
    j = 0;
    for k in range(p, r+1):
        if L[i] < R[j]:
            A[k] = L[i]
            i = i +1
        else:
            A[k] = R[j]
            j = j + 1

    return A


# 合并排序
# 从A[0]开始
def merge_sort(A, p, r):
    if p < r:
        q = int((p+r)/2)
        A = merge_sort(A, p, q)
        A = merge_sort(A, q+1, r)
        A = merge(A, p, q, r)

    return A

# 主函数
N = 20
A = gen_rand_n(N)

print (A)

A = merge_sort(A, 0, N-1)

print (A)
