
% 功能：演示SVM算法
% 基于 SVM 实现特征分类；
% 时间：2015-07-11

clc
clear all
close all


%% 测试样本
dataLength = 2;
dataNumber = [100, 100];

% 第一类
x1 = randn(dataLength, dataNumber(1));
y1 = ones(1, dataNumber(1));

% 第二类
x2 = 5 + randn(dataLength, dataNumber(2));
y2 = -ones(1, dataNumber(2));

% 显示
figure(1);
plot(x1(1,:), x1(2,:), 'bx', x2(1,:), x2(2,:), 'k.');
axis([-3 8 -3 8]);
title('SVM')
hold on

% 合并样本
X = [x1, x2];       
Y = [y1, y2];      

% 打乱样本顺序
index = randperm(sum(dataNumber));
X(:, index) = X;
Y(:, index) = Y;

%% SVM 训练
% line : w1x1 + w2x2 + b = 0
% weight = [b, w1, w2]
weight = svmTrainMine(X, Y);

%% 测试输出

% y = kx + b
k = -weight(2) / weight(3);
b = weight(1) / weight(3);

xLine = -2:0.1:7;
yLine = k .* xLine - b;
plot(xLine, yLine, 'r')
hold on

%% 查找支持向量
epsilon = 1e-5;
dist = abs(k .* X(1, :) - X(2,:) - b);
distSort = sort(dist);
i_sv = find(dist <= min(dist(:)) + epsilon);        
plot(X(1,i_sv), X(2,i_sv),'ro');


