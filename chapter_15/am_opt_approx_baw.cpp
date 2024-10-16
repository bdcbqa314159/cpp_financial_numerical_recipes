#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100;
    double X = 100;
    double sigma = 0.20;
    double r = 0.08;
    double b = -0.04;
    double time = 0.25;
    std::cout << " Call price using Barone-Adesi Whaley approximation = "
         << option_price_american_call_approximated_baw(S, X, r, b, sigma, time) << "\n";
    return 0;
}
