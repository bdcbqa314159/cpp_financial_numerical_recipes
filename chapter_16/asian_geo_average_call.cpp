#include "fin_recipes"
#include <iostream>

int main()
{
    double S = 100;
    double K = 100;
    double q = 0;
    double r = 0.06;
    double sigma = 0.25;
    double time = 1.0;
    std::cout << " Analytical geometric average = "
              << option_price_asian_geometric_average_price_call(S, K, r, q, sigma, time)
              << "\n";
    return 0;
}
