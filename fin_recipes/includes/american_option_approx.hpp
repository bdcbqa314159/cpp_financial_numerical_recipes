#pragma once
#include "definitions.hpp"

double option_price_american_put_approximated_johnson(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time);
double option_price_american_put_approximated_geske_johnson(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time);
double option_price_american_call_approximated_baw(c_double &S, c_double &K, c_double &r, c_double &b, c_double &sigma, c_double &time);
double option_price_american_call_approximated_bjerksund_stensland(c_double &S, c_double &K, c_double &r, c_double &b, c_double &sigma, c_double &T);
double option_price_american_put_approximated_bjerksund_stensland(c_double &S, c_double &K, c_double &r, c_double &b, c_double &sigma, c_double &T);
