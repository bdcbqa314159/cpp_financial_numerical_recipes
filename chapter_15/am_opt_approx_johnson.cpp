#include "fin_recipes"
#include <iostream>

int main()
{

    double r = 0.125;
    double S = 1.1;
    double X = 1;
    double sigma = 0.5;
    double time = 1;
    std::cout << " American put price using Johnson approximation = "
              << option_price_american_put_approximated_johnson(S, X, r, sigma, time)
              << "\n";
    return 0;
}
