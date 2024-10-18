#pragma once
#include "definitions.hpp"

double option_price_call_merton_jump_diffusion(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &T, c_double &lambda, c_double &kappa, c_double &delta);
double heston_call_option_price(c_double &S, c_double &K, c_double &r, c_double &v, c_double &tau, c_double &rho, c_double &kappa, c_double &lambda, c_double &theta, c_double &sigma);
