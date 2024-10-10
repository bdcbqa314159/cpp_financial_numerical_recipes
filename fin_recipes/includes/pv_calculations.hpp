#pragma once
#include <cmath>
#include <vector>
#include <iostream>
#include <cassert>
#include "definitions.hpp"

double cash_flow_pv_discrete(const v_double &, const v_double &, const double &);
double cash_flow_pv(const v_double &cflow_times, const v_double &, const double &);

const double ERROR = -1e30;

double cash_flow_irr_discrete(const v_double &, const v_double &);

inline int sgn(const double &r) { return r >= 0 ? 1 : -1; }

bool cash_flow_unique_irr(const v_double &, const v_double &);
