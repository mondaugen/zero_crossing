function [y] = zx_pulse(zc,T)
% return a signal that is zero everywhere except at the indices in zc
% where the y signal is marked with a single sample of value 1
% T is the multiple of zero crossings
%   1 is default, marks every zero-crossing
%   < 1 is not allowed
% other numbers indicate the number of zero-crossings per period, e.g., 2 will
% mark every other zero-crossing, 3 every third, etc.
if nargin<2, T=1; end;
N_zc = length(zc);
n_zc = 1:T:N_zc;
y(zc(n_zc)) = 1;
