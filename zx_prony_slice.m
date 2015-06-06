function [y] = zx_prony_slice(x,p,q,T)
% make a signal of pulses at every T zero crossings
% find the coefficients of a filter with p poles and q zeros that characterizes
% the signal between T consecutive zero crossings using prony's method
% synthesize a signal by concatenating the impulse responses of the filters,
% replacing each signal slice with this impulse response
zc = mark_zeroxs(x,0,1);
n_zc = [1:T:length(zc)];
bounds = [zc(n_zc)(1:end-1)' zc(n_zc)(2:end)']';
y = zeros(1,length(x));
for b = bounds,
    M = b(2)-b(1)+1;
    z = zeros(1,M);
    if (M>=4),
        if (p+q>=M),
            p_ = floor(M/2);
            q_ = floor(M/2) - 1;
            [A,B] = prony(x(b(1):b(2)),p_,q_);
        else
            [A,B] = prony(x(b(1):b(2)),p,q);
        end;
        z(1) = 1;
        z = filter(B,A,z);
    end; % if less than 4, just output zeros
    y(b(1):b(2)) = z;
end;
