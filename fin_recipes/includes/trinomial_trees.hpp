#pragma once
#include "definitions.hpp"

double option_price_put_american_trinomial(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &t, const size_t steps);
