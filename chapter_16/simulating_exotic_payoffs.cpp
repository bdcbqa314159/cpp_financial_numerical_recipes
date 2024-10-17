#include "fin_recipes"
#include <iostream>

int main()
{

    std::cout << "Testing general simulation of European options " << "\n";
    double S = 100;
    double K = 120;
    double r = 0.10;
    double time = 1.0;
    double sigma = 0.25;
    int no_sims = 10000;
    int no_steps = 250;
    double q = 0;
    std::cout << " simulated arithmetric average "
              << " S= " << S << " r= " << r << " price="
              << derivative_price_simulate_european_option_generic(S, K, r, sigma, time,
                                                                    payoff_arithmetic_average_call,
                                                                    no_steps, no_sims)
              << "\n";
    std::cout << " simulated geometric average = "
         << derivative_price_simulate_european_option_generic(S, K, r, sigma, time,
                                                              payoff_geometric_average_call,
                                                              no_steps, no_sims)
         << "\n";
    std::cout << " analytical lookback put = "
              << "option_price_european_lookback_put(S, S, r, q, sigma, time)"
              << "\n";
    std::cout << " simulated lookback put = "
         << derivative_price_simulate_european_option_generic(S, 0, r, sigma, time,
                                                              payoff_lookback_put,
                                                              no_steps, no_sims)
         << "\n";
    std::cout << " analytical lookback call = "
         << option_price_european_lookback_call(S, S, r, q, sigma, time)
         << "\n";
    std::cout << " simulated lookback call = "
         << derivative_price_simulate_european_option_generic(S, 0, r, sigma, time,
                                                              payoff_lookback_call,
                                                              no_steps, no_sims)
         << "\n";
    std::cout << " simulated lookback call using control variates = "
              << derivative_price_simulate_european_option_generic_with_control_variate(S, 0, r, sigma, time,
                                                                                        payoff_lookback_call,
                                                                                        no_steps, no_sims)
              << "\n";
    return 0;
}
