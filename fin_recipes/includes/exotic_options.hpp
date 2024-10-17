#pragma once
#include "definitions.hpp"

double option_price_put_bermudan_binomial(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &time, c_v_double &potential_exercise_times, const size_t &steps);
double option_price_asian_geometric_average_price_call(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &time);
double option_price_european_lookback_call(c_double &S, c_double &Smin, c_double &r, c_double &q, c_double &sigma, c_double &time);
double derivative_price_simulate_european_option_generic(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double payoff(c_v_double &prices, c_double &X), const size_t &no_steps, const size_t &no_sims);
double derivative_price_simulate_european_option_generic_with_control_variate(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double payoff(c_v_double &prices, c_double &X), const size_t &no_steps, const size_t &no_sims);

double payoff_arithmetic_average_call(c_v_double &prices, c_double &K);
double payoff_geometric_average_call(c_v_double &prices, c_double &K);
double payoff_lookback_call(c_v_double &prices, c_double &unused_var);
double payoff_lookback_put(c_v_double &prices, c_double &unused_var);
