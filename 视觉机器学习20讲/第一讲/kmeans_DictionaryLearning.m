% k-means 字典学习
% 参考：Learning Feature Representations with K-means
% 步骤: 
%      1. 图像分块，作为输入 
%      2. 输入归一化
%      3. 白化
%      4. K-means聚类

clc
clear all
close all

%% 读入图像
im = imread('leaves.tif');
if 3 == size(im, 3)
    im = rgb2gray(im);
end

im = double(im);

%% 提取图像块
N = 200; % 每个方向上图像块的个数
win = 16; % 图像块的大小为win*win
[row, col] = size(im);
numCol = fix(col / N);
numRow = fix(row / N);

idxLeftUpCol = 1:numCol:col-(win-1);
idxLeftUpRow = 1:numRow:row-(win-1);

winNum = size(idxLeftUpCol, 2) * size(idxLeftUpRow, 2); % 块的个数
patchs = zeros(win*win, winNum); % 所有块，样本

for i = 1:win
    for j = 1:win
        idx = (i-1) * win + j;
        patchOnePixel = im(idxLeftUpCol + i-1, idxLeftUpRow + j-1);
        patchs(idx, :) = patchOnePixel(:);
    end
end

%% 归一化
% x = (x-mean(x))/sqrt(var(x) + e)
% 在除以标准差的时候，为了避免分母为0和压制噪声，我们给标准差增加一个小的常数。
% 对于[0, 255]范围的灰度图，给方差加10一般是ok的

epsilon = 10; 
centerPatchs = bsxfun(@minus, patchs, mean(patchs, 2)); % 2，表示每一行求均值
patchs = bsxfun(@rdivide, centerPatchs, sqrt(var(patchs) + epsilon));

%% 白化
% [V, D] = eig(cov(x))，也就是说 VDV' = cov(x)
% x = V(D + epsilon*I)^(-0.5)V'x

epsilonZCA = 0.01;
[V, D] = eig(patchs * patchs'); % VDV' = cov(x)
patchs = V*((D + epsilonZCA * eye(size(D)))^(-0.5))*V'*patchs;

%% 聚类
NN = 16;
k = NN * NN; % 聚类个数
max_iter = 100; %最大迭代次数

[centroids, labels] = run_kmeans(patchs, k, max_iter); 

%% 显示
dictionary = zeros(NN * 16, NN * 16);
for i = 1:NN
    for j = 1:NN
        dx = reshape(centroids(:, (i-1)*NN+j), 16, 16);
        dx = dx - min(dx(:));
        dx = (dx / max(dx(:)))*255;
        dictionary((i-1)*16+1:i*16, (j-1)*16+1:j*16) = dx;
    end
end
figure
imshow(uint8(dictionary), [])

% imwrite(uint8(dictionary), 'withoutWhitening.jpg')

