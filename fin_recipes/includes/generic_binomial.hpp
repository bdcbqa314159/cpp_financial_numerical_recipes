#pragma once
#include "definitions.hpp"

double option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
double option_price_generic_binomial(c_double &S, c_double &K, double generic_payoff(c_double &S, c_double &K), c_double &r, c_double &sigma, c_double &t, const size_t &steps);
double option_price_delta_generic_binomial(c_double &S, c_double &K, double generic_payoff(c_double &S, c_double &K), c_double &r, c_double &sigma, c_double &t, const size_t &steps);
