function A = merge_sort(A, p, r)
if p < r
    q = fix((p+r)/2);
    A = merge_sort(A, p, q);
    A = merge_sort(A, q+1, r);
    A = merge(A, p, q, r);
end
