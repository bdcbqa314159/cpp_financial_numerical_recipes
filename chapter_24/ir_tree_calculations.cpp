#include "fin_recipes"
#include <iostream>
#include <vector>

int main()
{
     std::vector<v_double> tree = interest_rate_trees_gbm_build(0.1, 1.02, 0.99, 3);
     std::cout << " Interest rate tree: " << "\n";
     std::cout << " Time 0: " << tree[0][0] << "\n";
     std::cout << " Time 1: " << tree[1][0] << " " << tree[1][1] << "\n";
     std::cout << " Time 2: " << tree[2][0] << " " << tree[2][1] << " " << tree[2][2] << "\n";

     return 0;
}
