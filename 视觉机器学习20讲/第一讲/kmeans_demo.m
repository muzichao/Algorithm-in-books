%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%功能：演示Kmeans聚类算法在计算机视觉中的应用
%实现如何利用Kmeans聚类实现图像的分割；
%环境：Win7，Matlab2014a
%Modi: NUDT-VAP
%时间：2014-10-17
%
%说明：Lab色彩模型是由亮度（L）和有关色彩的a, b三个要素组成。L表示亮度（Luminosity），
%   ：a表示从洋红色至绿色的范围，b表示从黄色至蓝色的范围。L的值域由0到100，L=50时，就相
%   ：当于50%的黑；a和b的值域都是由+127至-128，其中+127 a就是红色，渐渐过渡到-128 a的
%   ：时候就变成绿色；同样原理，+127 b是黄色，-128 b是蓝色。所有的颜色就以这三个值交互
%   ：变化所组成。
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear;
close all;
clc;
%% 读取测试图像
im = imread('Peppers.bmp');
im = imresize(im, 0.5);
imshow(im), title('Imput image');

%% 转换图像的颜色空间得到样本
cform = makecform('srgb2lab'); % 创建一个颜色变换结构,创建变换结构使从srgb颜色空间转换到Lab颜色空间
lab = applycform(im, cform); % 应用变换结构C,使RGB图像转换到Lab颜色空间
ab = double(lab(:, :, 2:3)); % 提取Lab颜色空间的a、b维
nrows = size(lab, 1); 
ncols = size(lab, 2);
X = reshape(ab, nrows*ncols, 2)';

figure
scatter(X(1,:)', X(2,:)', 3, 'filled');  
box on; %显示颜色空间转换后的二维样本空间分布
%print -dpdf 2D1.pdf

%% 对样本空间进行Kmeans聚类
k = 3; % 聚类个数
max_iter = 100; %最大迭代次数

[centroids, labels] = run_kmeans(X, k, max_iter); 

%% 显示聚类分割结果
figure
scatter(X(1,:)', X(2,:)', 3, labels, 'filled'); %显示二维样本空间聚类效果
hold on; 

scatter(centroids(1,:), centroids(2,:), 60, 'r', 'filled');
hold on; 

scatter(centroids(1,:), centroids(2,:), 30, 'g', 'filled');
box on; 
hold off;
% print -dpdf 2D2.pdf

pixel_labels = reshape(labels, nrows, ncols);
rgb_labels = label2rgb(pixel_labels); % 转换标记矩阵到RGB图像

figure
imshow(rgb_labels),
title('Segmented Image')
% print -dpdf Seg.pdf

imwrite(rgb_labels, 'out.jpg')