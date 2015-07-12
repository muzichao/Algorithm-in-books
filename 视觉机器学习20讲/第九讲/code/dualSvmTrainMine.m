function w = dualSvmTrainMine(X, Y)
% Dual SVM Classification:
% w = dualSvmTrainMine(x,y); 
% min  1/2*x'*H*x + f'*x
% s.t. A*x <= b
%      Aeq*x = beq
%      lb <= x <= ub

dataNumber = size(X, 2);

H = (Y' * Y).*(X' * X);
f = -ones(dataNumber, 1);
A = -eye(dataNumber);
b = zeros(dataNumber, 1);
Aeq = Y;
beq = 0;

alpha  = quadprog(H, f, A, b, Aeq, beq);  

w = sum(bsxfun(@times, X, alpha' .* Y), 2);
save alpha alpha
index = find(alpha > 0.00001);
b = Y(index(1)) - w' * X(:, index(1));
w = [b; w];