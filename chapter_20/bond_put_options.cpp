#include "fin_recipes"
#include <iostream>

int main()
{
     double B = 100;
     double K = 100;
     double r = 0.05;
     double sigma = 0.1;
     double time = 1;
     std::cout << " zero coupon put option price = "
               << bond_option_price_put_zero_black_scholes(B, K, r, sigma, time) << "\n";
     v_double coupon_times{0.5};

     v_double coupons{1.};

     std::cout << " coupon bond put option price = "
               << bond_option_price_put_coupon_bond_black_scholes(B, K, r, sigma, time, coupon_times, coupons);
     std::cout << "\n";
     size_t steps = 100;
     std::cout << " zero coupon american put option price, binomial = "
               << bond_option_price_put_american_binomial(B, K, r, sigma, time, steps) << "\n";
     return 0;
}
