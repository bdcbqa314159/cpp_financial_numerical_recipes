#include <iostream>
#include "fin_recipes"

int main(){

    v_double times = {1,2};

    v_double cashflows = {10, 110};

    term_structure_flat_class tsflat(0.1);
    std::cout << " price = " << bonds_price(times, cashflows, tsflat) << "\n";
    std::cout << " duration = " << bonds_duration(times, cashflows, tsflat) << "\n";
    std::cout << " convexity = " << bonds_convexity(times, cashflows, tsflat) << "\n";

    return 0;
}
