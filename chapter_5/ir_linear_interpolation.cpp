#include <iostream>
#include <vector>
#include "fin_recipes"

int main(){

    v_double times = {0.1, 0.5, 1, 5, 10};
    v_double yields = {0.1, 0.2, 0.3, 0.4, 0.5};

    std::cout << " yields at times: " << "\n";
    std::cout << " t=0.1 " << term_structure_yield_linearly_interpolated(0.1, times, yields) << "\n";
    std::cout << " t=0.5 " << term_structure_yield_linearly_interpolated(0.5, times, yields) << "\n";
    std::cout << " t=1 " << term_structure_yield_linearly_interpolated(1, times, yields) << "\n";
    std::cout << " t=3 " << term_structure_yield_linearly_interpolated(3, times, yields) << "\n";
    std::cout << " t=5 " << term_structure_yield_linearly_interpolated(5, times, yields) << "\n";
    std::cout << " t=10 " << term_structure_yield_linearly_interpolated(10, times, yields) << "\n";

    return 0;
}
