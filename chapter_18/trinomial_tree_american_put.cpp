#include "fin_recipes"
#include <iostream>

int main()
{

     double S = 100.0;
     double r = 0.1;
     double time = 1.0;
     double K = 100.0;
     double q = 0;
     double sigma = 0.25;
     int no_steps = 100;
     std::cout << " american put = " << option_price_put_american_trinomial(S, K, r, q, sigma, time, no_steps) << "\n";

     return 0;
}
