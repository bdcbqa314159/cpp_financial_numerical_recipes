#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50.0;
    double K = 50.0;
    double r = 0.1;
    double sigma = 0.4;
    double time = 0.4167;
    size_t no_S_steps = 20;
    size_t no_t_steps = 11;
    std::cout << " explicit finite differences, european put price = ";
    std::cout << option_price_put_european_finite_diff_explicit(S, K, r, sigma, time, no_S_steps, no_t_steps)
              << "\n";
    std::cout << " explicit finite differences, american put price = ";
    std::cout << option_price_put_american_finite_diff_explicit(S, K, r, sigma, time, no_S_steps, no_t_steps)
              << "\n";

    return 0;
}
