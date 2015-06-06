function [P] = fit_cubic(x0,y0,x3,y3,x_min,y_min,x_max,y_max)
A = [   x0^3 x0^2 x0 1;
        x3^3 x3^2 x3 1;
        3*x_min^2 2*x_min 1 0;
        3*x_max^2 2*x_max 1 0;
        x_min^3 x_min^2 x_min 1;
        x_max^3 x_max^2 x_max 1 ];
b = [y0 y3 0 0 y_min y_max]';
P = linsolve(A'*A,A'*b);
endfunction
