#pragma once
#include "definitions.hpp"

double option_price_put_bermudan_binomial(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &time, c_v_double &potential_exercise_times, const size_t &steps);
double option_price_asian_geometric_average_price_call(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &time);
