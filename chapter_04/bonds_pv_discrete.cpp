#include "fin_recipes"
#include <iostream>

int main()
{

    v_double cflows{10, 10, 110}, times{1, 2, 3};
    double r = 0.09;

    std::cout << "bonds price = " << bonds_price_discrete(times, cflows, r) << "\n";
}
