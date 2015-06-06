function [P] = fit_zx_maxmin_cubic(x,st,en)
% FIT_ZX_MAXMIN_CUBIC
% Given the start and end indices of an array x, return the coefficients of the
% polynomial P that fits the end points and the maximum and minimum in a
% least-squares sense
[x_min, x_min_idx] = min(x(st:en));
[x_max, x_max_idx] = max(x(st:en));
x_min_idx += (st - 1);
x_max_idx += (st - 1);
A = [ st^3          st^2        st        1;
      en^3          en^3        en        1;
      3*x_min_idx^2 2*x_min_idx 1         0;  
      3*x_max_idx^2 2*x_max_idx 1         0;  
      x_min_idx^3   x_min_idx^3 x_min_idx 1;
      x_max_idx^3   x_max_idx^3 x_max_idx 1 ];
b = [x(st) x(en) 0 0 x(x_min_idx) x(x_max_idx)]';
P = linsolve(A' * A, A' * b);
endfunction
