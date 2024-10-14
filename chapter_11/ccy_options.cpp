#include "fin_recipes"
#include <iostream>

int main()
{

    double S = 50, K = 52, r = 0.08, r_f = 0.05, sigma = 0.2, time = 0.5; // verified with another site.

    std::cout << "european ccy call option =  \n";
    std::cout << currency_option_price_call_european(S,K,r,r_f,sigma,time) << "\n";

    return 0;
}
