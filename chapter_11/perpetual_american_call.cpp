#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50, K = 40, r = 0.05, q = 0.02, sigma = 0.05;

    std::cout << "perpetual american call price =  \n";
    std::cout << option_price_american_perpetual_call(S, K, r, q, sigma) << "\n";

    return 0;
}
