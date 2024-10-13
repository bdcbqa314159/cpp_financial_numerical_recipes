#include <iostream>
#include "fin_recipes"

int main(){

    double S = 100, K = 100, r = 0.025, u = 1.05, d = 1/u;

    std::cout<<"one period euro call option price = \n";
    std::cout<<option_price_call_euro_binomial_single_period(S, K, r, u, d)<<"\n";

    size_t no_periods = 2;
    std::cout<<"multi period euro call option price = \n";
    std::cout<<option_price_call_euro_binomial_multi_period_given_ud(S, K, r, u, d, no_periods)<<"\n";

    return 0;
}
