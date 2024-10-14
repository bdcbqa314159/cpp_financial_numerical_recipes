#pragma once
#include "definitions.hpp"

double option_price_european_call_payout(const double &S, const double &K, const double &r, const double &q, const double &sigma, const double &time);
double option_price_european_call_dividends(const double &S, const double &K, const double &r, const double &sigma, const double &time, const v_double &dividend_times, const v_double &dividends_flows);
