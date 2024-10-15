#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50.0;
    double K = 52.0;
    double r = 0.08;
    double rf = 0.05;
    double sigma = 0.2;
    double time = 0.5;
    int no_steps = 100;

    std::cout << "american ccy call option =  \n";
    std::cout << ccy_option_price_call_american_binomial(S, K, r, rf, sigma, time, no_steps) << "\n";

    return 0;
}
