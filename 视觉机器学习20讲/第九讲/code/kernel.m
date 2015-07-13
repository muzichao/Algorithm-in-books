function out = kernel(X, Y, Type)

switch Type
    case 'liner'
        out = X' * Y;
    case 'poly'
        out = (1 + X' * Y).^2;
    case 'gauss'
        numberX = size(X,2);
        numberY = size(Y,2);   
        tmp = zeros(numberX, numberY);
        for i = 1:numberX
            for j = 1:numberY
                tmp(i,j) = norm(X(:,i)-Y(:,j));
            end
        end        
        out = exp(-0.5*(tmp).^2);        
    otherwise
        out = 0;
end

        