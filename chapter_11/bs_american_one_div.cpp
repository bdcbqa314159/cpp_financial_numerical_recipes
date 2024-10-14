#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100, K = 100, r = 0.1, sigma = 0.25, tau = 1., tau1 = 0.5, D1 = 10.;

    std::cout << "american call price with one dividend =  \n";
    std::cout << option_price_american_call_one_dividend(S, K, r, sigma, tau, D1, tau1) << "\n";

    return 0;
}
