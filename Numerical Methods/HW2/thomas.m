function x = thomas(dig_below, dig_main, dig_above, b)
% Thomas Algorithm or Tridiagonal matrix algorithm is a
% Gaussian Elimination variant that requires O(n) flops
% and it can be used on tridiagonal matrices as we are
% doing here. So, we will implement the Thomas Algorithm.

% dig_below and dig_above are vectors of size n-1
% dig_main and b are vectors of size n

[~, n] = size(dig_main);
x = zeros(1, n);

for i=2:n
    x(1,i) = dig_below(1, i-1) / dig_main(1, (i-1));
    dig_main(1, i) = dig_main(1, i) - (x(1, i) * dig_above(1, i-1));
    b(1, i) = b(1, i) - (x(1, i) * b(1,i-1));
end

% Time for the back substitution

x(1, n) = b(1,n)/dig_main(1,n);

for i=(n-1):-1:1
    x(1, i) = (b(1, i) - (x(1, i + 1) * dig_above(1, i)))/(dig_main(1, i));
end

end
