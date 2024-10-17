#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{

    std::cout << "Testing here ...\n";
    std::vector<double> cflows{-100., 75., 75.}, times{0., 1., 2.};
    double r = 0.1;

    std::cout << "Present value, 10pct discretely compounded interest = " << cash_flow_pv_discrete(times, cflows, r) << "\n";

    return 0;
}
