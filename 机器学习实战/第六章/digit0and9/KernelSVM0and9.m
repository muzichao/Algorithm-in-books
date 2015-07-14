% 功能：演示 Kernel SVM算法
% 时间：2015-07-13

clc
clear all
close all

addpath('./data');

%% 测试样本
dataLength = 2;
[xTrain1, yTrain1, xTrain2, yTrain2] = readDataFromFiles('./data/trainingDigits');
[xTest1, yTest1, xTest2, yTest2] = readDataFromFiles('./data/testDigits');

% 合并样本
X = [xTrain1, xTrain2];       
Y = [yTrain1, yTrain2];      

% X = [xTest1, xTest2];       
% Y = [yTest1, yTest2]; 
% 打乱样本顺序
index = randperm(size(X, 2));
X(:, index) = X;
Y(:, index) = Y;

% img = zeros(14*32, 14*32);
% for i = 1:14
%     for j = 1:14
%         if ((i-1)*14+j <= 186)
%             img((i-1)*32+1:i*32, (j-1)*32+1:j*32) = flip(imrotate(reshape(X(:, (i-1)*14+j),[32, 32]), -90), 2);
%         end
%     end
% end
% figure
% imshow(img, [])
% imwrite(uint8(img*255), 'test.jpg')
% break
%% Kernel SVM 训练
kernelType = 'liner';
[alpha, b] = kernelSvmTrainMine(X, Y, kernelType);

%% 提取 SV
epsilon = 1e-5; 
indexSV = find(alpha > epsilon);

%% 测试输出
yTestResult1 = sign(sum(bsxfun(@times, alpha(indexSV) .* Y(indexSV)', kernel(X(:, indexSV), xTest1, kernelType))) + b);
yTestResult2 = sign(sum(bsxfun(@times, alpha(indexSV) .* Y(indexSV)', kernel(X(:, indexSV), xTest2, kernelType))) + b);

sum(yTestResult1 ~= yTest1)
sum(yTestResult2 ~= yTest2)