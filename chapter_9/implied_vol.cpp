#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50;
    double K = 50;
    double r = 0.10;
    double time = 0.50;
    double C = 2.5;
    std::cout << " Black Scholes implied volatility using Newton search = ";
    std::cout << option_price_implied_volatility_call_black_scholes_newton(S, K, r, time, C) << "\n";
    std::cout << " Black Scholes implied volatility using bisections = ";
    std::cout << option_price_implied_volatility_call_black_scholes_bisections(S, K, r, time, C) << "\n";

    return 0;
}
