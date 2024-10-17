#include "fin_recipes"
#include <iostream>

int main()
{

    term_structure_flat_class ts(0.05);
    double t1 = 1;
    std::cout << "discount factor t1 = " << t1 << ":" << ts.d(t1) << "\n";
    double t2 = 2;
    std::cout << "discount factor t2 = " << t2 << ":" << ts.d(t2) << "\n";
    std::cout << "spot rate t = " << t1 << ":" << ts.r(t1) << "\n";
    std::cout << "spot rate t = " << t2 << ":" << ts.r(t2) << "\n";
    std::cout << "forward rate from t1= " << t1 << " to t2= " << t2 << ":"
              << ts.f(t1, t2) << "\n";

    return 0;
}
