function roots = secant_method(f, start_pt, end_pt, tol)
  % This is our g(x) function and x_k_1 = x_(k-1)
  g = @(x_k, x_k_1) x_k + ((f(x_k)*abs(x_k - x_k_1))/(f(x_k) - f(x_k_1)));
    
  
  % Since we will probe small subintervals, middle of the two points
  % might be a good place to start
  x_k = (start_pt + end_pt) / 2;
  x_k_1 = end_pt;
  no_significant_decrease = false;
  x_k_1_temp = x_k_1;
    
  % While conditions are not met, we will continue to iterate.
  % Since NOT of A.B is A' + B', we put the NOT version of the
  % root finding condition for the loop.
  while((abs(x_k - x_k_1) >= (tol * (1 + abs(x_k)))) || abs(f(x_k)) >= tol)
    if (f(x_k) >= (0.5 * f(x_k_1)))
      no_significant_decrease = true;
          %bisect three times then secant method again
    for z=1:3
      first = start_pt;
      last = end_pt;
      middle = (first + last)/(2);
      if (f(first) * f(middle) < 0)
        last = middle;
      else
        first = middle;
      end
    end
    roots = secant_method(f, first, last, tol);
      break;
    end
    x_k_1_temp = x_k_1;
    x_k_1 = x_k;
    x_k = g(x_k, x_k_1_temp);
  end
    
  if (~no_significant_decrease)
    roots = x_k;
  end

end
