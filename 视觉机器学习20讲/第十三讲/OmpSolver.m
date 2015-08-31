function result = OmpSolver(trn, tst)

nTrain = size(trn.X, 2);    % 训练样本数
nTest = size(tst.X, 2);    % 测试样本数
kClass = max(trn.y);       % 类别数
onesvecs = full(ind2vec(trn.y));    % kClass x nTrain 
   
% OMP 参数
param.L = 20;
param.eps = 0.1;
     
% 训练集归一化
Atilde = zeros(size(trn.X));
for i = 1:nTrain
    Atilde(:,i) = trn.X(:,i) / norm(trn.X(:,i), 2);
end

deltavec = zeros(nTrain, kClass);
residual = zeros(kClass, nTest);

% 所有测试样本逐个分类
for iter = 1:nTest  
    % 测试样本归一化
    ytilde = tst.X(:, iter);
    ytilde = ytilde / norm(ytilde);        

    % OMP 方法求解
     xp = mexOMP(ytilde, Atilde, param);

    % 决策
    for i=1:kClass
        deltavec(:, i) = onesvecs(i, :)' .* xp;
        residual(i, iter) = norm(ytilde - Atilde * deltavec(:, i));
    end
end

[~, IX] = sort(residual); % 对每一列进行排序
result = IX(1, :); % 提取第一行