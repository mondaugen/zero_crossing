function [P] = fit_zxmmc(x,st,en)
% FIT_ZX_MAXMIN_CUBIC
% Given the start and end indices of an array x, return the coefficients of the
% polynomial P that fits the end points and the maximum and minimum in a
% least-squares sense
[x_min, x_min_idx] = min(x(st:en));
[x_max, x_max_idx] = max(x(st:en));
x_min_idx += (st - 1);
x_max_idx += (st - 1);
P = fit_cubic(st,x(st),en,x(en),x_min_idx,x_min,x_max_idx,x_max);
endfunction
