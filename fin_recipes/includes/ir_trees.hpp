#pragma once
#include "definitions.hpp"
#include <vector>

std::vector<v_double> interest_rate_trees_gbm_build(c_double &r0, c_double &u, c_double &d, const size_t n);
double interest_rate_trees_gbm_value_of_cashflows(c_v_double &cflow, const std::vector<v_double> &r_tree, c_double &q);
double interest_rate_trees_gbm_value_of_callable_bond(c_v_double &cflow, const std::vector<v_double> &r_tree, c_double &q, const size_t &first_call_time, c_double &call_price);
