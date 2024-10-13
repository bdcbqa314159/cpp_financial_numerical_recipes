#pragma once
#include <vector>

double option_price_call_euro_binomial_single_period(const double &S, const double &X, const double &r, const double &u, const double &d);
std::vector<std::vector<double>> binomial_tree(const double &S0, const double &u, const double &d, const size_t no_steps);
double option_price_call_euro_binomial_multi_period_given_ud(const double &S0, const double &K, const double &r, const double &u, const double &d, const size_t no_periods);
