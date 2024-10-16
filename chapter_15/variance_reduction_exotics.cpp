#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100;
    double K = 100;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1;
    int no_sims = 50000;
    std::cout << "cash or nothing, Q=1:"
              << derivative_price_simulate_european_generic(S, K, r, sigma, time, pay_off_cash_or_nothing, no_sims) << "\n";
    std::cout << "control variate = "
              << derivative_price_simulate_european_generic_with_control_variate(S, K, r, sigma, time, pay_off_cash_or_nothing, no_sims)
              << "\n";
    std::cout << "antithetic variate = "
              << derivative_price_simulate_european_generic_with_antithetic_variate(S, K, r, sigma, time,
                                                                                    pay_off_cash_or_nothing, no_sims)
              << "\n";
    std::cout << "asset or nothing:"
              << derivative_price_simulate_european_generic(S, K, r, sigma, time, pay_off_asset_or_nothing, no_sims) << "\n";
    std::cout << "control variate = "
              << derivative_price_simulate_european_generic_with_control_variate(S, K, r, sigma, time, pay_off_asset_or_nothing, no_sims)
              << "\n";
    std::cout << "antithetic variate = "
              << derivative_price_simulate_european_generic_with_antithetic_variate(S, K, r, sigma, time,
                                                                                    pay_off_asset_or_nothing, no_sims)
              << "\n";

    return 0;
}
