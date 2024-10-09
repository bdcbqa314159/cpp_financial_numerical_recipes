#pragma once
#include "definitions.hpp"

double bonds_price_discrete(const v_double&, const v_double&, const double&);
double bonds_yield_to_maturity(const v_double&, const v_double&, const double&);
double bonds_duration_discrete(const v_double &, const v_double &, const double &);
double bonds_duration_macaulay_discrete(const v_double &, const v_double &, const double &);
double bonds_duration_modified_discrete(const v_double &, const v_double &, const double &);
double bonds_convexity_discrete(const v_double &, const v_double &, const double &);

double bonds_price(const v_double &, const v_double &, const double &);
double bonds_duration(const v_double &, const v_double &, const double &);
double bonds_duration_macaulay(const v_double &, const v_double &, const double &);
double bonds_convexity(const v_double &, const v_double &, const double &);
