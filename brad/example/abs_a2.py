# $begin abs_a2.py$$ $newlinech #$$
#
# $section abs: Example and Test$$
#
# $index abs, example$$
# $index example, abs$$
#
# $code
# $verbatim%example/abs_a2.py%0%# BEGIN CODE%# END CODE%1%$$
# $$
# $end
# BEGIN CODE
from cppad import *
def test_abs_a2() :
  x   = array( [ ad(-1),  ad(0),  ad(1)] )
  n   = len(x)
  a_x = independent(x)
  a_y = abs( a_x )
  f   = adfun(a_x, a_y)
  f.forward(0, x)
  dx  = array( list( ad(0) for i in range(n) ) )
  for i in range( n ) :
    dx[i] = ad(0)
  for i in range( n ) :
    dx[i] = ad(1)
    df    = f.forward(1, dx)
    if x[i] >= 0 :
      assert df[i] == +1.
    else :
      assert df[i] == -1.
    dx[i] = ad(-1)
    df    = f.forward(1, dx)
    if x[i] > 0 :
      assert df[i] == -1.
    else :
      assert df[i] == +1.
    dx[i] = ad(0)
# END CODE
