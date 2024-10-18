#include "credit_risk.hpp"
#include "option_pricing_bs.hpp"
#include <cmath>

double debt_value(c_double& V, c_double& F, c_double& r, c_double& sigma, c_double& T){
    double p = option_price_put_black_scholes(V,F,r,sigma,T);
    double debt = std::exp(-r*T)*F - p;
    return debt;
}
