#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100, K = 100, r = 0.1, sigma = 0.25, time = 1, div_yield = 0.05;
    v_double div_times{0.25, 0.75};
    v_double div_flows{2.5, 2.5};

    std::cout << "european stock call option with continuous dividend = \n";
    std::cout << option_price_european_call_payout(S, K, r, div_yield, sigma, time) << "\n";

    std::cout << "european stock call option with discrete dividend = \n";
    std::cout << option_price_european_call_dividends(S, K, r, sigma, time, div_times, div_flows) << "\n";

    return 0;
}
