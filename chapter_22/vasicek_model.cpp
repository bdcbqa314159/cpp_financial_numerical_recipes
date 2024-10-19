#include "fin_recipes"
#include <iostream>

int main()
{
     std::cout << "Example term structure calculation using the Vasicek term structure model"
          << "\n";
     double r = 0.05;
     double a = -0.1;
     double b = 0.1;
     double sigma = 0.1;
     std::cout << " direct calculation, discount factor (t=1): "
          << term_structure_discount_factor_vasicek(1, r, a, b, sigma) << "\n";
     term_structure_class_vasicek vc(r, a, b, sigma);
     std::cout << " using a term structure class " << "\n";
     std::cout << " yield (t=1) = " << vc.r(1) << "\n";
     std::cout << " discount factor (t=1) = " << vc.d(1) << "\n";
     std::cout << " forward rate (t1=1, t2=2) = " << vc.f(1, 2) << "\n";

     return 0;
}
