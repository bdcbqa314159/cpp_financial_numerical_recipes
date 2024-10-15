#pragma once
#include "definitions.hpp"

double option_price_call_european_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
double option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
double option_price_delta_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
void option_price_partials_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, double &delta, double &gamma, double &theta, double &vega, double &rho);
double option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &y, c_double &sigma, c_double &t, const size_t &steps);
double option_price_call_american_proportional_dividends_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, c_v_double &div_times, c_v_double &div_flows);
double option_price_call_american_discrete_dividends_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, c_v_double &div_times, c_v_double &div_flows);
double futures_option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
double ccy_option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &r_f, c_double &sigma, c_double &t, const size_t &steps);
