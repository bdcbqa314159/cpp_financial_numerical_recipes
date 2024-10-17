#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100.0;
    double K = 100.0;
    double r = 0.1;
    double sigma = 0.25;
    double time_to_maturity = 1.0;
    int steps = 100;
    std::cout << " american call price = "
         << option_price_generic_binomial(S, K, pay_off_call, r, sigma, time_to_maturity, steps)
         << "\n";
    std::cout << " american put price = "
         << option_price_generic_binomial(S, K, pay_off_put, r, sigma, time_to_maturity, steps)
         << "\n";

    K = 120.;

    std::cout << " binary option price = "
              << option_price_generic_binomial(S, K, pay_off_binary_call, r, sigma, time_to_maturity, steps)
              << "\n";

    return 0;
}
