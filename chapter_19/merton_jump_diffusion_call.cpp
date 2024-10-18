#include "fin_recipes"
#include <iostream>

int main()
{
     double S = 100;
     double K = 100;
     double r = 0.05;
     double sigma = 0.3;
     double T = 1;
     double lambda = 0.5;
     double kappa = 0.5;
     double delta = 0.5;
     std::cout << " Merton Jump diffusion call = "
               << option_price_call_merton_jump_diffusion(S, K, r, sigma, T, lambda, kappa, delta)
               << "\n";

     return 0;
}
