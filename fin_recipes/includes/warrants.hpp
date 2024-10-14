#pragma once

const double EPSILON = 1e-6;

double warrant_price_adjusted_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time, const double &m, const double &n);
