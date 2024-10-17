#include "fin_recipes"
#include <iostream>

int main()
{

    std::cout << " Black Scholes call partial derivatives " << "\n";
    double S = 50;
    double K = 50;
    double r = 0.10;
    double sigma = 0.30;
    double time = 0.50;
    double Delta, Gamma, Theta, Vega, Rho;
    option_price_partials_call_black_scholes(S, K, r, sigma, time, Delta, Gamma, Theta, Vega, Rho);
    std::cout << " Delta = " << Delta << "\n";
    std::cout << " Gamma = " << Gamma << "\n";
    std::cout << " Theta = " << Theta << "\n";
    std::cout << " Vega = " << Vega << "\n";
    std::cout << " Rho = " << Rho << "\n";
    return 0;
}
