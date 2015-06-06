function [zc] = mark_zeroxs(x,side,x_l)
% MARK_ZEROXS returns the indices of the zero crossings in x
%   x is the signal to analyse
%   side is the side to start on (1 == positive)
%   x_l is the last non-zero sample of the previous iteration. If run for the
%   first time set this to 1.
m = 0; % number of zero crossings
x_r = 0;
for n = [1:length(x)],
    if (side == 0),
        if (x(n) < 0),
            x_l = n;
        end
        if (x(n) > 0),
            x_r = n;
            m += 1;
            zc(m) = floor(x_l + (x_r - x_l) / 2);
            side = 1;
        end
    else,
        if (x(n) > 0),
            x_l = n;
        end
        if (x(n) < 0),
            x_r = n;
            m += 1;
            zc(m) = floor(x_l + (x_r - x_l) / 2);
            side = 0;
        end
    end
end
endfunction
