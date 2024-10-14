#include "fin_recipes"
#include <iostream>

int main()
{

    // double F = 50, K = 45, r = 0.08, sigma = 0.2, time = 0.5; -> the book results for this are not correct.
    double F = 12800, K = 12750, r = 0.01, sigma = 0.15, time = 0.25; // verified with another site.

    std::cout << "european futures call option =  \n";
    std::cout << futures_option_price_call_european_black(F,K,r,sigma,time) << "\n";

    return 0;
}
