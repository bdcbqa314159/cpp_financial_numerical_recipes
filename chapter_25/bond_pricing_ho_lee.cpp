#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{
     double delta = 0.98;
     double pi = 0.5;
     double r = 0.1;
     term_structure_class *initial = new term_structure_flat_class(r);
     v_double times{5.};
     v_double cflows{100};


     double K = 80;
     double time_to_maturity = 3;
     std::cout << " Flat term structure " << "\n";
     std::cout << " c= " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times, cflows, K ,time_to_maturity);
     std::cout << "\n";
     delete (initial);
     double beta0=0.09; double beta1=0.01; double beta2=0.01; double lambda=5.0;
     initial = new term_structure_class_nelson_siegel(beta0,beta1,beta2,lambda);
     std::cout << " Nelson Siegel term structure " << "\n";
     std::cout << " c= " << price_european_call_option_on_bond_using_ho_lee(initial, delta, pi, times, cflows, K, time_to_maturity);
     std::cout << "\n";
     return 0;
}
