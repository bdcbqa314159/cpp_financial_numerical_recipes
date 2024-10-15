#pragma once
#include "definitions.hpp"

double simulate_lognormal_random_variable(c_double &S, c_double &r, c_double &sigma, c_double &time);
double option_price_call_european_simulated(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_sims);
double option_price_delta_call_european_simulated(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_sims);

double pay_off_call(c_double &S, c_double &K);
double pay_off_put(c_double &S, c_double &K);

double derivative_price_simulate_european_generic(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims);
double derivative_price_simulate_european_generic_with_control_variate(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims);
double derivative_price_simulate_european_generic_with_antithetic_variate(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims);

double pay_off_cash_or_nothing(c_double &S, c_double &K);
double pay_off_asset_or_nothing(c_double &S, c_double &K);
