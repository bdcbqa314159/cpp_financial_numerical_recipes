#pragma once

double option_price_call_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time);
double option_price_put_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time) ;
double option_price_delta_call_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time);
double option_price_delta_put_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time);
void option_price_partials_call_black_scholes(const double &S, const double &K, const double &r, const double &sigma, const double &time, double &delta, double &gamma, double &theta, double &vega, double &rho);
double option_price_implied_volatility_call_black_scholes_bisections(const double &S, const double &K, const double &r, const double &time, const double &option_price);

double option_price_implied_volatility_call_black_scholes_newton(const double &S,
                                                                 const double &K,
                                                                 const double &r,
                                                                 const double &time,
                                                                 const double &option_price);
