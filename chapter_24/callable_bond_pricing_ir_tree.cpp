#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{
     double r0 = 0.06;
     double u = 1.2;
     double d = 0.9;
     int n = 10;
     double q = 0.5;
     std::vector<v_double> tree = interest_rate_trees_gbm_build(r0, u, d, n);
     v_double cashflows{0, 6, 6, 6, 6, 6, 6, 6, 6, 6, 106};

     std::cout << "Straight bond price = " << interest_rate_trees_gbm_value_of_cashflows(cashflows, tree, q) << "\n";
     int first_call_time = 6;
     double call_price = 106;
     std::cout << "Callable bond price = "
          << interest_rate_trees_gbm_value_of_callable_bond(cashflows, tree, q, first_call_time, call_price) << "\n";

     return 0;
}
