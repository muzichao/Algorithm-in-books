% 【函数描述】C=bsxfun(fun,A,B)：两个数组间元素逐个计算，fun是函数句柄或者m文件，也可以为如下内置函数 
%          @plus 加 
%          @minus 减 
%          @times 数组乘 
%          @rdivide 左除 
%          @ldivide 右除 
% For example： 如何将一个矩阵的每行或每列元素分别扩大不同的倍数？
%               如[1 2 3;4 5 6 ;7 8 9],第一列元素乘以1，第二列元素以2，第三列元素乘以4。
% 利用bsxfun函数，可以给出下列代码：
% 
% a = [1,2,3;4,5,6;7,8,9];
% acol = bsxfun(@times,a,[1 2 4])
function [centroids, labels] = run_kmeans(X, k, max_iter)
% 该函数实现Kmeans聚类
% 输入参数：
%                   X为输入样本集，dxN
%                   k为聚类中心个数
%                   max_iter为kemans聚类的最大迭代的次数
% 输出参数：
%                   centroids为聚类中心 dxk
%                   labels为样本的类别标记

%% 采用K-means++算法初始化聚类中心
% k-means++算法选择初始seeds的基本思想就是：初始的聚类中心之间的相互距离要尽可能的远。
%
% 1. 从输入的数据点集合中随机选择一个点作为第一个聚类中心
% 2. 对于数据集中的每一个点x，计算它与最近聚类中心(指已选择的聚类中心)的距离D(x)
% 3. 选择一个新的数据点作为新的聚类中心，选择的原则是：D(x)较大的点，被选取作为聚类中心的概率较大
% 4. 重复2和3直到k个聚类中心被选出来
% 5. 利用这k个初始的聚类中心来运行标准的k-means算法
% 
% 
% 1. 先从我们的数据库随机挑个随机点当“种子点”
% 2. 对于每个点，我们都计算其和最近的一个“种子点”的距离D(x)并保存在一个数组里，然后把这些距离加起来得到Sum(D(x))。
% 3. 然后，再取一个随机值，用权重的方式来取计算下一个“种子点”。这个算法的实现是，先取一个能落在Sum(D(x))中的随机值
%    Random，然后用Random -= D(x)，直到其<=0，此时的点就是下一个“种子点”。
% 4. 重复2和3直到k个聚类中心被选出来
% 5. 利用这k个初始的聚类中心来运行标准的k-means算法
%
% 第3步的核心思想：Sum(D(x))*random时，该值会以较大的概率落入D(x)较大的区间内，所以对应的点会以较大的概率被选中作为
% 新的聚类中心。|-----5-----|----------10----------|----4----|

  centroids = X(:, 1 + round(rand * (size(X, 2)-1))); % 从输入的数据点集合中随机选择一个点作为第一个聚类中心
  labels = ones(1, size(X, 2)); % 初始化每个数据点的标号为1
  for i = 2:k
%         pp = centroids(:, labels);
        D = X - centroids(:, labels); % 计算每一个点与聚类中心的差值
        D = sqrt(dot(D, D, 1));% 每一点与聚类中心的差值的二范数
        D = cumsum(D); % 累积求和，便于查找下一个种子点
        if D(end) == 0, 
            centroids(:, i:k) = X(:, ones(1, k-i+1)); 
            return; 
        end
        nextCentroid = find(rand < D / D(end), 1); % 查找下一聚类中心点的坐标，Random -= D(x)，直到其<=0
        centroids(:, i) = X(:, nextCentroid); % 添加新的聚类中心
%         a = 2*real(centroids' * X);
%         b = dot(centroids, centroids, 1).';
        [~, labels] = max(bsxfun(@minus, 2*real(centroids' * X), dot(centroids, centroids, 1).'));
  end
  
%% 标准Kmeans算法
  for iter = 1:max_iter
        for i = 1:k, 
            l = labels==i; 
            centroids(:,i) = sum(X(:, l), 2) / sum(l); 
        end
        [~, labels] = max(bsxfun(@minus, 2*real(centroids' * X), dot(centroids,centroids,1).'), [], 1);
  end
  
end
