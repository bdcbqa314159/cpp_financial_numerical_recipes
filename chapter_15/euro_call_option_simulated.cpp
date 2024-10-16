#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 100.0;
    double K = 100.0;
    double r = 0.1;
    double sigma = 0.25;
    double time = 1.0;
    size_t no_sims = 5000;
    std::cout << " call: black scholes price = " << option_price_call_black_scholes(S, K, r, sigma, time) << "\n";
    std::cout << " simulated price = "
              << option_price_call_european_simulated(S, K, r, sigma, time, no_sims) << "\n";
    // std::cout << " put: black scholes price = " << option price put black scholes(S, K, r, sigma, time) << endl;
    // std::cout << " simulated price = "
    //      << option price put european simulated(S, K, r, sigma, time, no sims) << endl;

    return 0;
}
