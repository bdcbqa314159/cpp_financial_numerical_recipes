#pragma once
#include "definitions.hpp"

double bond_option_price_call_zero_american_rendleman_bartter(c_double &K, c_double opt_mat, c_double &S, c_double &M, c_double &interest, c_double &bond_mat, c_double &mat_payment, const size_t &no_steps);
