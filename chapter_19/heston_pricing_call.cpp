#include "fin_recipes"
#include <iostream>

int main()
{
     double S = 100;
     double K = 100;
     double r = 0.01;
     double v = 0.01;
     double tau = 0.5;
     double rho = 0;
     double kappa = 2;
     double lambda = 0.0;
     double theta = 0.01;
     double sigma = 0.01;
     std::cout << "heston call price "
          << heston_call_option_price(S, K, r, v, tau, rho, kappa, lambda, theta, sigma) << "\n";

     return 0;
}
