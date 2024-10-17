#include "fin_recipes"
#include <iostream>

int main()
{
    double S = 100; double K = 100; double r = 0.1;
    double sigma = 0.25;
    double time = 1.0;
    size_t no_sims = 50000;
    std::cout << "Black Scholes call option price = " << option_price_call_black_scholes(S, K, r, sigma, time) << "\n";
    std::cout << "Simulated call option price = "
         << derivative_price_simulate_european_generic(S, K, r, sigma, time, pay_off_call, no_sims)
         << "\n";
    // std::cout << "Black Scholes put option price = " << option price put black scholes(S, K, r, sigma, time) << "\n";
    std::cout << "Simulated put option price = "
              << derivative_price_simulate_european_generic(S, K, r, sigma, time, pay_off_put, no_sims)
              << "\n";

    return 0;
}
