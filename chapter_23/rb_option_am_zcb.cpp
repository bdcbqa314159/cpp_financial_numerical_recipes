#include "fin_recipes"
#include <iostream>

int main()
{
     double K = 950;
     double S = 0.15;
     double M = 0.05;
     double interest = 0.10;
     double option_maturity = 4;
     double bond_maturity = 5;
     double bond_maturity_payment = 1000;
     size_t no_steps = 100;
     std::cout << " Rendleman Bartter price of option on zero coupon bond: ";
     std::cout << bond_option_price_call_zero_american_rendleman_bartter(K, option_maturity, S, M,
                                                                    interest, bond_maturity,
                                                                    bond_maturity_payment, no_steps)<<"\n";

     return 0;
}
