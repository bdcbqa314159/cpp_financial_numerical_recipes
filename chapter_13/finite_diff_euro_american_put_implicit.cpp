#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50.0;
    double K = 50.0;
    double r = 0.1;
    double sigma = 0.4;
    double time = 0.5;
    size_t no_S_steps = 200;
    size_t no_t_steps = 200;
    // std::cout << " black scholes put price = " << option price put black scholes(S, K, r, sigma, time) << "\n";
    std::cout << " implicit Euro put price = ";
    std::cout << option_price_put_european_finite_diff_implicit(S, K, r, sigma, time, no_S_steps, no_t_steps) << "\n";
    std::cout << " implicit American put price = ";
    std::cout << option_price_put_american_finite_diff_implicit(S, K, r, sigma, time, no_S_steps, no_t_steps) << "\n";

    return 0;
}
