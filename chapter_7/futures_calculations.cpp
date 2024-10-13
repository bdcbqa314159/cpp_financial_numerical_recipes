#include <iostream>
#include "fin_recipes"

int main(){

    double S = 100, r = 0.1, time = 0.5;
    std::cout << "Futures price = " << futures_price(S, r, time) << "\n";

    return 0;
}
