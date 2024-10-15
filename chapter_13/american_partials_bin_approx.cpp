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
    double delta{}, gamma{}, theta{}, vega{}, rho{};
    option_price_partials_call_american_binomial(S, K, r, sigma, time, no_steps,
                                                 delta, gamma, theta, vega, rho);
    std::cout << " Call price partials " << "\n";
    std::cout << " delta = " << delta << "\n";
    std::cout << " gamma = " << gamma << "\n";
    std::cout << " theta = " << theta << "\n";
    std::cout << " vega = " << vega << "\n";
    std::cout << " rho = " << rho << "\n";

    double delta_1 = option_price_delta_call_american_binomial(S, K, r, sigma, time, no_steps);
    std::cout<<"delta1 = "<<delta_1<<"\n";

    return 0;
}
