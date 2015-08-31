function result = AnnBpSolver(Train, Test)

nTrain = size(Train.X, 2);    % 训练样本数
kClass = max(Train.y);       % 类别数

nPerm = randperm(nTrain); % 从 1 到 nTrain 间随机排序
input_train = Train.X;
output_train = zeros(1, kClass * nTrain);
output_train(kClass .* (0:nTrain-1)' + Train.y') = 1;
output_train = reshape(output_train, [kClass, nTrain]);

input_train = input_train(:, nPerm(1 : nTrain));
output_train = output_train(:, nPerm(1 : nTrain));

input_test = Test.X;

%% 网络结构初始化
inNum = size(Train.X, 1);
midNum = 100;
outNum = kClass;
 
% 权值初始化
epsilonInit = sqrt(6) / sqrt(inNum + outNum);
W10 = rands(midNum, inNum) * epsilonInit;
W21 = rands(outNum, midNum) * epsilonInit;

% 学习率
eta = 0.05;

% 输入数据归一化
[input_train, inputps] = mapminmax(input_train);

%% 网络训练
iterMax = 500;
eIter = zeros(iterMax, 1);
step = 10;
for iter = 1:iterMax
    for n = 1:step:nTrain
        nEnd = min(n+step-1, nTrain);
        % 取一个样本
        oneIn = input_train(:, n:nEnd);
        oneOut = output_train(:, n:nEnd);
        oneIn = oneIn';
        oneOut = oneOut';
        
        % 隐藏层输出 
        hOut = 1 ./ (1 + exp(- oneIn * W10'));

        % 输出层输出
        yOut = hOut * W21';
        
        % 计算误差
        eOut = oneOut - yOut;     
        eIter(iter) = eIter(iter) + sum(sum(abs(eOut)));
        
        % 计算输出层误差项 delta2
        delta2 = eOut;
        
        % 计算隐藏层误差项 delta1
        FI = hOut .* (1 - hOut);
        delta1 = (FI .* (eOut * W21));

        % 更新权重
        W21 = W21 + eta / step * delta2' * hOut;
        W10 = W10 + eta / step * delta1' * oneIn;
    end
end
%% 测试
input_test = mapminmax('apply', input_test, inputps);

% 隐藏层输出 
hOut = 1 ./ (1 + exp(- W10 * input_test));

% 输出层输出
fore = W21 * hOut;

%% 结果分析
% 根据网络输出找出数据属于哪类
[result, ~] = find(bsxfun(@eq, fore, max(fore)) ~= 0);