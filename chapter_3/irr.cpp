#include "fin_recipes"
#include <vector>

int main()
{
    std::vector<double> cflows{-100., 10., 110.}, times{0., 1., 2.};
    double r = 0.05;

    std::cout << " present value, 5 percent discretely compounded interest = ";
    std::cout << cash_flow_pv_discrete(times, cflows, r) << "\n";
    std::cout << " internal rate of return, discrete compounding = ";
    std::cout << cash_flow_irr_discrete(times, cflows) << "\n";

    return 0;
}
