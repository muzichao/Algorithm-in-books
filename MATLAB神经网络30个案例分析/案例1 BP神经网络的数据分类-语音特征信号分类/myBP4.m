
%% 清空环境变量
clc
clear
tic
%% 训练数据预测数据提取及归一化

% 下载四类语音信号
load data1 c1
load data2 c2
load data3 c3
load data4 c4

% 四个特征信号矩阵合成一个矩阵
data(1:500,:) = c1(1:500,:);
data(501:1000,:) = c2(1:500,:);
data(1001:1500,:) = c3(1:500,:);
data(1501:2000,:) = c4(1:500,:);

% 输入输出数据,第1维为类别标识，后24维为语音特征信号
input = ones(size(data));
input(:,2:25) = data(:,2:25);

outputClass = data(:, 1);
output(4 .* (0:2000-1)' + outputClass) = 1;
output = (reshape(output, [4, 2000]))';

% 随机提取1500个样本为训练样本，500个样本为预测样本
nPerm = randperm(2000); % 从1到2000间随机排序
input_train = input(nPerm(1:1500), :)';
output_train = output(nPerm(1:1500), :)';
input_test = input(nPerm(1501:2000), :)';
output_test = output(nPerm(1501:2000), :)';

% 输入数据归一化
[inputn,inputps] = mapminmax(input_train);

%% 网络结构初始化
innum = 25;
midnum = 26;
outnum = 4;
 
% 权值初始化
w01 = rands(midnum, innum);
w12 = rands(outnum, midnum);

% 学习率
eta = 0.1;

%% 网络训练
iterMax = 50;
eIter = zeros(iterMax, 1);
for iter = 1:iterMax
    for n = 1:1500
        % 取一个样本
        oneIn = inputn(:, n);
        oneOut = output_train(:, n);
        
        % 隐藏层输出             
        hOut = 1 ./ (1 + exp(- w01 * oneIn));

        % 输出层输出
        yOut = w12 * hOut;
        
        % 计算误差
        eOut = oneOut - yOut;     
        eIter(iter) = eIter(iter) + sum(abs(eOut));
        
        % 计算输出层误差项 delta2
        delta2 = eOut;
        
        % 计算隐藏层误差项 delta1
        FI = hOut .* (1 - hOut);
        delta1 = (FI .* (eOut' * w12)');
        
        % 更新权重
        w01 = w01 + eta * delta1 * oneIn';
        w12 = w12 + eta * delta2 * hOut';
    end
end
 

%% 语音特征信号分类
inputn_test = mapminmax('apply', input_test, inputps);

% 隐藏层输出 
hOut = 1 ./ (1 + exp(- w01 * inputn_test));

% 输出层输出
fore = w12 * hOut;

%% 结果分析
% 根据网络输出找出数据属于哪类
[output_fore, ~] = find(bsxfun(@eq, fore, max(fore)) ~= 0);

%BP网络预测误差
error = output_fore' - outputClass(nPerm(1501:2000))';

%% 计算正确率
% 找出每类判断错误的测试样本数
kError = zeros(1,4);  
outPutError = bsxfun(@and, output_test, error);
[indexError, ~] = find(outPutError ~= 0);

for class = 1:4
    kError(class) = sum(indexError == class);
end

% 找出每类的总测试样本数
kReal = zeros(1, 4);
[indexRight, ~] = find(output_test ~= 0);
for class = 1:4
    kReal(class) = sum(indexRight == class);
end

% 正确率
rightridio = (kReal-kError) ./ kReal
meanRightRidio = mean(rightridio)

toc

%% 画图
% 画出预测语音种类和实际语音种类的分类图
figure(1)
plot(output_fore,'r')
hold on
plot(outputClass(nPerm(1501:2000))', 'b')
legend('预测语音类别', '实际语音类别')

% 画出误差图
figure(2)
plot(error)
title('BP网络分类误差', 'fontsize',12)
xlabel('语音信号', 'fontsize',12)
ylabel('分类误差', 'fontsize',12)

% 画目标函数
figure(3)
plot(eIter)
title('每次迭代总的误差', 'fontsize', 12)
xlabel('迭代次数', 'fontsize', 12)
ylabel('所有样本误差和', 'fontsize', 12)

