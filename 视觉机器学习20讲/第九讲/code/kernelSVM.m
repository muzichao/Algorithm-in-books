% 功能：演示 Kernel SVM算法
% 时间：2015-07-13

clc
clear all
close all

%% 测试样本
dataLength = 2;
dataNumber = [50, 50];

% 第一类
x1 = randn(dataLength, dataNumber(1));
y1 = ones(1, dataNumber(1));

% 第二类
x2 = 3.5 + randn(dataLength, dataNumber(2));
y2 = -ones(1, dataNumber(2));

% xrand = 8 * (rand(dataLength, dataNumber(1)+dataNumber(2)) - 0.5);
% % 第一类-圆
% x1 = xrand(:, sum(xrand .* xrand, 1) > 3) + 3;
% dataNumber(1) = size(x1, 2);
% y1 = ones(1, dataNumber(1));
% 
% % 第二类-圆
% x2 = xrand(:, sum(xrand .* xrand, 1) <= 3) + 3;
% dataNumber(2) = size(x2, 2);
% y2 = -ones(1, dataNumber(2));

% 显示
figure(1);
plot(x1(1,:), x1(2,:), 'bx', x2(1,:), x2(2,:), 'k.');
axis([-3 8 -3 8]);
title('Kernel SVM')
hold on

% 合并样本
X = [x1, x2];       
Y = [y1, y2];      

% 打乱样本顺序
index = randperm(sum(dataNumber));
X(:, index) = X;
Y(:, index) = Y;

%% Kernel SVM 训练
kernelType = 'poly';
[alpha, b] = kernelSvmTrainMine(X, Y, kernelType);

%% 提取 SV
epsilon = 1e-5; 
indexSV = find(alpha > epsilon);

%% 标记 SV
plot(X(1,indexSV), X(2,indexSV), 'ro');
hold on

%% 测试输出
[x1, x2] = meshgrid(-2:0.1:7, -2:0.1:7);
[rows, cols] = size(x1);
nt = rows * cols;                 
Xt = [reshape(x1,1,nt); reshape(x2,1,nt)];

Yd = sign(sum(bsxfun(@times, alpha(indexSV) .* Y(indexSV)', kernel(X(:, indexSV), Xt, kernelType))) + b);

Yd = reshape(Yd, rows, cols);
contour(x1,x2,Yd,[0 0],'m');   
hold off;