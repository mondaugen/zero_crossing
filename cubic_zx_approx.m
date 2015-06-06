function [y] = cubic_zx_approx(x)
zc = mark_zeroxs(x,0,1);
n_zc = [1:2:length(zc)];
bounds = [zc(n_zc)(1:end-1)' zc(n_zc)(2:end)']';
ps = zeros(4,size(bounds)(2));
y = zeros(1,length(x));
c_ps = 1;
for b = bounds,
    ps(:,c_ps) = fit_zxmmc(x,b(1),b(2))';
    y(b(1):b(2)) = polyval(ps(:,c_ps),[b(1):b(2)]);
    c_ps += 1;
end
