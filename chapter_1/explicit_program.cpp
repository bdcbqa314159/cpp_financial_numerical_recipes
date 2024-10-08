#include <iostream>
#include <cmath>

double power(double, double);

int main()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "2 ^" << i << " is " << power(2, i) << "\n";
    }
}

double power(double x, double n)
{
    return std::exp(n * std::log(x));
}