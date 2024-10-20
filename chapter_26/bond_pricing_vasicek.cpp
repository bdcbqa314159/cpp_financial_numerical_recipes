#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{
     double a = 0.1;
     double b = 0.1;
     double sigma = 0.02;
     double r = 0.05;
     double X = 0.9;
     std::cout << " Vasicek call option price "
          << bond_option_price_call_zero_vasicek(X, r, 1, 5, a, b, sigma) << "\n";
     return 0;
}
