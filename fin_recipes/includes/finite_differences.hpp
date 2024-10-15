#pragma once
#include "definitions.hpp"

double option_price_put_european_finite_diff_explicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps);
double option_price_put_american_finite_diff_explicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps);
double option_price_put_american_finite_diff_implicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps);
double option_price_put_european_finite_diff_implicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps);
