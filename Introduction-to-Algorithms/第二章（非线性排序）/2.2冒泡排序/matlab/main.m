% 算法导论-第二章-2.2
% 冒泡排序
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 冒泡排序就是把小的元素往前调或者把大的元素往后调
% 比较相邻的元素。如果第一个比第二个大，就交换他们两个。
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% BUBBLE-SORT（A）
% bubble_sort(A)
% {
%    for i = 1 to length[A]
%    {
%        for j = length[A] to i+1
%        {
%            if A[j] < A[j-1]
%            {
%                 exchane A[j] and A[j-1];
%            }
%        }
%    }
% }
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2014. 09. 09
% lichao

clc
clear all
close all

N = 10; % 数组长度

A = randperm(N);

A

for i = 1:N
    for j = N:-1:i+1
        temp = 0;
        if A(j) < A(j-1)
            temp = A(j);
            A(j) = A(j-1);
            A(j-1) = temp;
        end
    end
end
A