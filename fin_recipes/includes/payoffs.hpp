#pragma once
#include "definitions.hpp"

double pay_off_call(c_double &S, c_double &K);
double pay_off_put(c_double &S, c_double &K);
double pay_off_cash_or_nothing(c_double &S, c_double &K);
double pay_off_asset_or_nothing(c_double &S, c_double &K);

double pay_off_binary_call(c_double &S, c_double &K);
double pay_off_binary_put(c_double &S, c_double &K);

double payoff_arithmetic_average_call(c_v_double &prices, c_double &K);
double payoff_geometric_average_call(c_v_double &prices, c_double &K);
double payoff_lookback_call(c_v_double &prices, c_double &unused_var);
double payoff_lookback_put(c_v_double &prices, c_double &unused_var);
