#include <iostream>
#include "fin_recipes"

int main(){

    v_double cflows{10, 10, 110}, times{1, 2, 3};
    double r = 0.09;

    std::cout<<"bonds price = "<<bonds_price_discrete(times, cflows, r)<<"\n";
    std::cout<<"bond duration = "<<bonds_duration_discrete(times, cflows, r)<<"\n";
    std::cout<<"bond macaulay = "<<
        bonds_duration_macaulay_discrete(times, cflows, bonds_price_discrete(times, cflows, r))<<"\n";

    return 0;
}
