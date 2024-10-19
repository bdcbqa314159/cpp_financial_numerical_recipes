#include "fin_recipes"
#include <iostream>

int main()
{
     std::cout << "Example calculations using the Cox Ingersoll Ross term structure model " << "\n";
     double r = 0.05;
     double kappa = 0.01;
     double sigma = 0.1;
     double theta = 0.08;
     double lambda = 0.0;
     std::cout << " direct calculation, discount factor (t=1): "
          << term_structure_discount_factor_cir(1, r, kappa, lambda, theta, sigma) << "\n";
     std::cout << " using a class " << "\n";
     term_structure_class_cir cir(r, kappa, lambda, theta, sigma);
     std::cout << " yield (t=1) = " << cir.r(1) << "\n";
     std::cout << " discount factor (t=1) = " << cir.d(1) << "\n";
     std::cout << " forward (t1=1, t2=2) = " << cir.f(1, 2) << "\n";

     return 0;
}
