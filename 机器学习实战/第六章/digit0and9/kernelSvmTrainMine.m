function [alpha, b] = kernelSvmTrainMine(X, Y, kernelType)
% Kernel SVM Classification:
% [alpha, b] = kernelSvmTrainMine(x,y); 
% min  1/2*x'*H*x + f'*x
% s.t. A*x <= b
%      Aeq*x = beq
%      lb <= x <= ub

dataNumber = size(X, 2);

H = (Y' * Y) .* kernel(X, X, kernelType);
f = -ones(dataNumber, 1);
A = -eye(dataNumber);
b = zeros(dataNumber, 1);
Aeq = Y;
beq = 0;

alpha  = quadprog(H, f, A, b, Aeq, beq);  

% ÌáÈ¡ SV
epsilon = 1e-5; 
indexSV = find(alpha > epsilon);

b = mean(Y(indexSV) - (alpha(indexSV)' .* Y(indexSV)) * kernel(X(:, indexSV), X(:, indexSV), kernelType));