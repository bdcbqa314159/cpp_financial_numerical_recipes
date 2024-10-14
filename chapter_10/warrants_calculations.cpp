#include <iostream>
#include "fin_recipes"

int main(){

    double S = 48, K = 40, r = 0.08, sigma = 0.3, time = 0.5, m = 1000, n = 10000;
    double w = warrant_price_adjusted_black_scholes(S, K, r, sigma, time, m, n);
    std::cout<<"warrant price = \n";
    std::cout<<w<<"\n";

    return 0;
}
