#include "fin_recipes"
#include <iostream>

int main()
{
    double S = 100.0;
    double K = 100.0;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1.0;
    size_t no_steps = 100;
    std::cout << " european call= " << option_price_call_european_binomial(S, K, r, sigma, time, no_steps) << "\n";
    std::cout << " american call= " << option_price_call_american_binomial(S, K, r, sigma, time, no_steps) << "\n";
    // std::cout << " american put = " << option price put american binomial(S, K, r, sigma, time, no steps) << endl;
    return 0;
}
