#pragma once
#include "definitions.hpp"

double bond_option_price_put_zero_black_scholes(c_double &B, c_double &K, c_double &r, c_double &sigma, c_double &time);
double bond_option_price_put_coupon_bond_black_scholes(c_double &B, c_double &K, c_double &r, c_double &sigma, c_double &time, c_v_double &coupon_times, c_v_double &coupon_flows);
double bond_option_price_put_american_binomial(c_double &B, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps);
