#include "fin_recipes"
#include <iostream>

int main()
{
     std::cout << "Example term structure calculations using a cubic spline " << "\n";
     double b = 0.1;
     double c = 0.1;
     double d = -0.1;
     v_double f{0.01,0.01,-0.01};

     v_double knots{2, 7, 12};

     std::cout << " direct calculation, discount factor (t=1) "
          << term_structure_discount_factor_cubic_spline(1, b, c, d, f, knots) << "\n";
     std::cout << " Using a term structure class " << "\n";
     term_structure_class_cubic_spline cs(b, c, d, f, knots);
     std::cout << " yield (t=1) = " << cs.r(1) << "\n";
     std::cout << " discount factor (t=1) = " << cs.d(1) << "\n";
     std::cout << " forward (t1=1, t2=2) = " << cs.f(1, 2) << "\n";

     return 0;
}
