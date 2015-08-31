%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% “基于K近邻”，“稀疏表示”，“人工神经网络”实现人脸识别；
% 实验中采用 SPAMS工具箱和Yale人脸数据库
% SPAMS下载地址 ： http://spams-devel.gforge.inria.fr/
% 环境：Win7，Matlab 2014a
% 时间：2015-08-30
% 部分参考《视觉机器学习20讲》
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clc
clear all
close all

addpath(genpath('spams-matlab'));
addpath(genpath('CNN'))

%% 读入数据
load trainData.mat;
load testData.mat
nTest = size(Test.y, 2);

%% 1. K 近邻分类
tic
ID1 = knnclassify(Test.X', Train.X', Train.y);
time(1) = toc;
correctSample = sum(ID1 == Test.y');
accuracy(1) = correctSample / nTest;
fprintf('K 近邻分类：        精度 = %.2f%%；重构时间为： %.2fs\n', accuracy(1) * 100, time(1));

%% 2. 稀疏表示-OMP求解
tic
ID2 = OmpSolver(Train, Test);
time(2) = toc;
correctSample = sum(ID2 == Test.y);
accuracy(2) = correctSample / nTest;
fprintf('稀疏表示-OMP求解：   精度 = %.2f%%；重构时间为： %.2fs\n', accuracy(2) * 100, time(2));

%% 3. 稀疏表示-APG求解
tic
ID3 = ApgSolver(Train, Test);
time(3) = toc;
correctSample = sum(ID3 == Test.y);
accuracy(3) = correctSample / nTest;
fprintf('稀疏表示-APG求解：   精度 = %.2f%%；重构时间为： %.2fs\n', accuracy(3) * 100, time(3));

%% 4. 人工神经网络-BP求解
tic
ID4 = AnnBpSolver(Train, Test);
time(4) = toc;
correctSample = sum(ID4 == Test.y');
accuracy(4) = correctSample / nTest;
fprintf('人工神经网络-BP求解： 精度 = %.2f%%；重构时间为： %.2fs\n', accuracy(4) * 100, time(4));

