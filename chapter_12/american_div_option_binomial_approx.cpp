#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100.0;
    double r = 0.10;
    double K = 100, sigma = 0.25;
    double time = 1.0;
    size_t no_steps = 100;
    double d = 0.02;
    std::cout << " call price with continuous dividend payout = "
              << option_price_call_american_binomial(S, K, r, d, sigma, time, no_steps) << "\n";
    v_double dividend_times{0.25, 0.75};
    v_double dividend_yields{0.025, 0.025};

    std::cout << " call price with proportial dividend yields at discrete dates = "
              << option_price_call_american_proportional_dividends_binomial(S, K, r, sigma, time, no_steps,
                                                                            dividend_times, dividend_yields)
              << "\n";
    v_double dividend_amounts{2.5,2.5};

    std::cout << " call price with proportial dividend amounts at discrete dates = "
              << option_price_call_american_discrete_dividends_binomial(S, K, r, sigma, time, no_steps,
                                                                        dividend_times, dividend_amounts)
              << "\n";

    return 0;
}
