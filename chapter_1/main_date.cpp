#include "fin_recipes"
#include <iostream>

int main()
{
    std::cout << "Working with dates...\n";

    date d{2024, 1, 1};

    for (size_t i = 0; i < 75; ++i)
    {
        std::cout << d << "\n";
        d++;
    }

    return 0;
}
