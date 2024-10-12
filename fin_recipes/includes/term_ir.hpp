#pragma once
#include "definitions.hpp"
#include "term_structure.hpp"

double term_structure_yield_from_discount_factor(const double &, const double &);
double term_structure_discount_factor_from_yield(const double &, const double &);
double term_structure_forward_rate_from_discount_factors(const double &, const double &, const double &);
double term_structure_forward_rate_from_yields(const double &, const double &, const double &, const double &);
double term_structure_yield_linearly_interpolated(const double &, const v_double &, const v_double &);

double bonds_price(const v_double &, const v_double &, const term_structure_class &);
double bonds_duration(const v_double &, const v_double &, const term_structure_class &);
double bonds_convexity(const v_double &, const v_double &, const term_structure_class &);
