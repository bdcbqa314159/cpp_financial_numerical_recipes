#pragma once
#include "definitions.hpp"

double option_price_european_call_payout(const double &S, const double &K, const double &r, const double &q, const double &sigma, const double &time);
double option_price_european_call_dividends(const double &S, const double &K, const double &r, const double &sigma, const double &time, const v_double &dividend_times, const v_double &dividends_flows);
double option_price_american_call_one_dividend(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &tau, c_double &D1, c_double &tau1);
double futures_option_price_call_european_black(c_double &F, c_double &K, c_double &r, c_double &sigma, c_double &time);
double currency_option_price_call_european(c_double &S, c_double &K, c_double &r, c_double &r_f, c_double &sigma, c_double &time);
double option_price_american_perpetual_call(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma);
