#include <iostream>
#include "fin_recipes"

int main(){

    v_double cflows{10, 10, 110}, times{1, 2, 3};
    double r = 0.09;

    double B = bonds_price_discrete(times, cflows, r);

    std::cout<< "bonds price = "<<B<<"\n";
    std::cout<<"bond duration = "<<bonds_duration_discrete(times, cflows, r)<<"\n";
    std::cout<<"bond duration modified = "<<bonds_duration_modified_discrete(times, cflows,B)<<"\n";
    std::cout<<"bond convexity = "<<bonds_convexity_discrete(times, cflows, r)<<"\n";
    std::cout<<"new bond price = "<<bonds_price_discrete(times, cflows, 0.1)<<"\n";

    return 0;
}
