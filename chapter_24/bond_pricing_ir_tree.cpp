#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{
     double r0 = 0.1;
     double u = 1.02;
     double d = 0.99;
     int n = 3;
     double q = 0.5;
     std::vector<v_double> tree = interest_rate_trees_gbm_build(r0, u, d, n);
     v_double cashflows{0, 10, 10, 110};

     std::cout << "Bond price B = " << interest_rate_trees_gbm_value_of_cashflows(cashflows, tree, q)<<"\n";
     return 0;
}
