function w = svmTrainMine(X, Y)
% SVM Classification:
%   w = svmTrain(x,y); 

dataLength = size(X, 1);
dataNumber = size(X, 2);

H = eye(dataLength+1);
H(1, 1) = 0;
f = zeros(dataLength+1, 1);
A = zeros(dataNumber, dataLength+1);
A = bsxfun(@plus, A, -Y');
A(:, 2:end) = A(:, 2:end) .* X';
b = -ones(dataNumber, 1);

w  = quadprog(H,f,A,b);  
