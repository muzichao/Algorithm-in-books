
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
input = data(:,2:25);

output1 = data(:, 1);
output(4 .* (0:2000-1)' + output1) = 1;
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
innum = 24;
midnum = 25;
outnum = 4;
 

% 权值初始化
w1 = rands(midnum, innum);
b1 = rands(midnum, 1);
w2 = rands(midnum, outnum);
b2 = rands(outnum, 1);


% 学习率
xite = 0.1;

%% 网络训练
iterMax = 30;
eIter = zeros(iterMax, 1);
for iter = 1:iterMax
    for n = 1:1500
        % 取一个样本
        oneInput = inputn(:, n);
        oneOutput = output_train(:, n);
        
        % 隐含层输出       
        hOut = w1 * oneInput + b1;       
        hScore = 1 ./ (1 + exp(-hOut));

        % 输出层输出
        yOut = w2' * hScore + b2;
        
        % 计算误差
        e = oneOutput - yOut;     
        eIter(iter) = eIter(iter) + sum(abs(e));
        
        % 计算权值变化率
        dw2 = e * hScore';
        db2 = e';
        
        S = hScore;
        FI = S .* (1 - S);
        
        ew2 = (w2 * e)';
        db1 = FI' .* ew2;
        dw1 = oneInput * db1;
        
        % 更新权重
        w1 = w1 + xite * dw1';
        b1 = b1 + xite * db1';
        w2 = w2 + xite * dw2';
        b2 = b2 + xite * db2';   
    end
end
 

%% 语音特征信号分类
inputn_test = mapminmax('apply',input_test,inputps);

% 隐含层输出 
hOut = bsxfun(@plus, w1 *inputn_test, b1);
hScore = 1 ./ (1 + exp(-hOut));

% 输出层输出
fore = bsxfun(@plus, w2' * hScore, b2);


%% 结果分析
% 根据网络输出找出数据属于哪类
[output_fore, ~] = find(bsxfun(@eq, fore, max(fore)) ~= 0);

%BP网络预测误差
error = output_fore' - output1(nPerm(1501:2000))';

% 画出预测语音种类和实际语音种类的分类图
figure(1)
plot(output_fore,'r')
hold on
plot(output1(nPerm(1501:2000))','b')
legend('预测语音类别','实际语音类别')

% 画出误差图
figure(2)
plot(error)
title('BP网络分类误差','fontsize',12)
xlabel('语音信号','fontsize',12)
ylabel('分类误差','fontsize',12)

% 画目标函数值
figure(3)
plot(eIter)
title('每次迭代总的误差','fontsize',12)
xlabel('迭代次数','fontsize',12)
ylabel('所有样本误差和','fontsize',12)
%% 计算正确率
%找出判断错误的分类属于哪一类
kError = zeros(1,4);  
outPutError = bsxfun(@and, output_test, error);
[indexError, ~] = find(outPutError ~= 0);

for n = 1:4
    kError(n) = sum(indexError == n);
end

%找出每类的个体和
kReal = zeros(1, 4);
[indexRight, ~] = find(output_test ~= 0);
for n = 1:4
    kReal(n) = sum(indexRight == n);
end

%正确率
rightridio = (kReal-kError) ./ kReal
meanRightRidio = mean(rightridio)
toc