function [y] = spline_zx_minmax_approx(x)
zc = mark_zeroxs(x,0,1);
n_zc = [1:2:length(zc)];
bounds = [zc(n_zc)(1:end-1)' zc(n_zc)(2:end)']';
max_indices = zeros(1,size(bounds)(2));
min_indices = zeros(1,size(bounds)(2));
n_ind = 1;
for b = bounds,
    [m, mi] = max(x(b(1):b(2)));
    max_indices(n_ind) = mi + b(1) -1;
    [m, mi] = min(x(b(1):b(2)));
    min_indices(n_ind) = mi + b(1) -1;
    n_ind += 1;
end;
indices = sort([zc min_indices max_indices]);
y = spline(indices,x(indices),[1:length(x)]);
