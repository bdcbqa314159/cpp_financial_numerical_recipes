#include "fin_recipes"
#include <iostream>

int main()
{

    v_double cflows{10, 10, 110}, times{1, 2, 3};
    double r = 0.09;

    double B = bonds_price(times, cflows, r);

    std::cout << "bonds price = " << B << "\n";
    std::cout << "bond duration = " << bonds_duration(times, cflows, r) << "\n";
    std::cout << "bond convexity = " << bonds_convexity(times, cflows, r) << "\n";
    std::cout << "new bond price = " << bonds_price(times, cflows, 0.08) << "\n";

    return 0;
}
