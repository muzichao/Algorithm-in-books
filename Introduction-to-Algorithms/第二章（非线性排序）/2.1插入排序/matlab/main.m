% 算法导论-第二章-2.1
% 插入排序
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% INSERTION-SORT（A）
% for j <- 2 to length[A]
%     do key <- A[j]
%         Insert A[j] into the sorted sequence A[1...j-1].
%         i <- j-1
%         while i>0 and A[i]>key
%             do A[i+1] <- A[i]
%                 i <- i-1
%         A[i+1] <- key
% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% 2014. 09. 08
% lichao

clc
clear all
close all

N = 1000; % 数组长度

A = randperm(N);

for j = 2:N
    key = A(j);
    i = j-1;
    while i > 0 & A(i) > key
        A(i+1) = A(i);
        i = i-1;
    end
    A(i+1) = key;
end


