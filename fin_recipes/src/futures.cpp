#include "futures.hpp"

double futures_price(const double &S, const double &r, const double &T)
{
    return S * std::exp(r * T);
}
