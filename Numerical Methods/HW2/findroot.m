function roots = findroot(f, a, b, nprobe, tol)
  % Returns a root value equal to zero given the function, range, 
  % equidistance and tolerance.

  % We will be looping through the given function in order to
  % get to subintervals and determine if it changes sign in that
  % interval. To do that, we will multiply f(a_i)*f(b_i) where a_i
  % and b_i are the points are subinterval starts and check if sign
  % of the result is negative. If it is negative, we will use Secant
  % method to find x* where x* is the root.
  
  roots = [];
  i = a;
  while (i <= b)
    if(f(i) * f(i + nprobe) > 0)
      i = i + nprobe;
      continue
    end
    % The subinterval we are on has at least one change in sign.
    % Now, we will use Secant method so we don't have to calculate
    % the derivative of the given function.
    start_pt = i;
    end_pt = i + nprobe;
    roots = [roots, secant_method(f, start_pt, end_pt, tol)];
    i = i + nprobe;
  end 
end
