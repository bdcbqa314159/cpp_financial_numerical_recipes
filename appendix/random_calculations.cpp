#include "fin_recipes"
#include <iostream>

int main()
{

    std::cout << " 5 random uniform numbers between 0 and 1: " << "\n";
    std::cout << " ";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << " " << random_uniform_0_1();
    };
    std::cout << "\n";
    std::cout << " 5 random normal(0,1) numbers: " << "\n";
    std::cout << " ";
    for (int i = 0; i < 5; ++i)
    {
        std::cout << " " << random_normal();
    };
    std::cout << "\n";
    return 0;
}
