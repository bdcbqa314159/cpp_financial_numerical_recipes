#include "fin_recipes"
#include <iostream>

int main()
{
     double beta0 = 0.01;
     double beta1 = 0.01;
     double beta2 = 0.01;
     double lambda = 5.0;
     double t = 1.0;
     std::cout << "Example calculations using the Nelson Siegel term structure approximation"
          << "\n";
     std::cout << " direct calculation, yield = "
          << term_structure_yield_nelson_siegel(t, beta0, beta1, beta2, lambda) << "\n";
     term_structure_class_nelson_siegel ns(beta0, beta1, beta2, lambda);
     std::cout << " using a term structure class" << "\n";
     std::cout << " yield (t=1) = " << ns.r(t) << "\n";
     std::cout << " discount factor (t=1) = " << ns.d(t) << "\n";
     std::cout << " forward rate (t1=1, t2=2) = " << ns.f(1, 2) << "\n";

     return 0;
}
