#include <iostream>
#include "fin_recipes"

int main(){

    v_double cflows{10, 10, 110}, times{1, 2, 3};
    double r = 0.09, B = bonds_price_discrete(times, cflows, r);

    std::cout<<"bond price = "<<bonds_price_discrete(times, cflows, r)<<"\n";
    std::cout<<"bond ytm = "<<bonds_yield_to_maturity(times, cflows, B)<<"\n";

}
