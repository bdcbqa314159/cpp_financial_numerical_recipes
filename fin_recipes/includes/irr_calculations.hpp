#pragma once
#include <cmath>
#include <algorithm>
#include <vector>
#include <cassert>
#include "pv_calculations.hpp"
#include "definitions.hpp"

const double ERROR = -1e30;

double cash_flow_irr_discrete(const v_double &, const v_double &);

inline int sgn(const double &r) { return r >= 0 ? 1 : -1; }

bool cash_flow_unique_irr(const v_double &, const v_double &);
