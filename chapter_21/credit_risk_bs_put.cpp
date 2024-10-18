#include "fin_recipes"
#include <iostream>

int main()
{
     std::cout << " Credit Risk Calculation \n";
     double V = 100;
     double F = 90;
     double r = 0.05;
     double T = 1;
     double sigma = 0.25;
     double p = option_price_put_black_scholes(V, F, r, sigma, T);
     std::cout << " Debt value = " << debt_value(V, F,r,sigma,T)<<"\n";
     return 0;
}
