function  A = merge(A, p, q, r)
n1 = q - p + 1;
n2 = r - q;

L = zeros(1, n1+1);
R = zeros(1, n2+1);
L(1:n1) = A(p:q);
R(1:n2) = A(q+1:r);

L(n1+1) = inf;
R(n2+1) = inf;

i = 1;
j = 1;

for k = p:r
    if L(i) < R(j)
        A(k) = L(i);
        i = i+1;
    else
        A(k) = R(j);
        j = j+1;
    end
end
