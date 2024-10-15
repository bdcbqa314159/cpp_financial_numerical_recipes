#include "fin_recipes"
#include <iostream>

int main()
{

    double F = 50.0;
    double r = 0.08;
    double K = 45.0;
    double sigma = 0.2;
    double time = 0.5;
    int no_steps = 100;
    std::cout << " european futures call option = "
         << futures_option_price_call_american_binomial(F, K, r, sigma, time, no_steps) << "\n";

    return 0;
}
