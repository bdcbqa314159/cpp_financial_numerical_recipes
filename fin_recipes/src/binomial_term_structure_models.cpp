#include "binomial_term_structure_models.hpp"
#include <algorithm>
#include <vector>

double bond_option_price_call_zero_american_rendleman_bartter(c_double& K, c_double opt_mat, c_double& S, c_double& M, c_double& interest, c_double& bond_mat, c_double& mat_payment, const size_t& no_steps){

    double delta_t = bond_mat/no_steps;
    double u = std::exp(S*std::sqrt(delta_t));
    double d = 1./u;

    double p_up = (std::exp(M*delta_t) - d)/(u-d);
    double p_down = 1. - p_up;

    v_double r(no_steps+1);
    r[0] = interest*std::pow(d, no_steps);
    double uu = u*u;
    for (size_t i = 1; i<=no_steps; ++i) r[i] = uu*r[i-1];
    v_double P(no_steps+1);
    for (size_t i = 0; i<=no_steps; ++i) P[i] = mat_payment;
    int no_call_steps = static_cast<int>(no_steps*opt_mat/bond_mat);

    for (int curr_step = no_steps; curr_step>no_call_steps; --curr_step){
        for (size_t i = 0; i<curr_step; ++i){
            r[i] *= u;
            P[i] = std::exp(-r[i]*delta_t)*(p_down*P[i] + p_up*P[i+1]);
        }
    }
    v_double C(no_call_steps+1);
    for (size_t i = 0; i<=no_call_steps; ++i) C[i] = std::max(0., P[i]-K);
    for (int curr_step = no_call_steps; curr_step>=0; --curr_step){
        for (size_t i = 0; i<curr_step; ++i){
            r[i] *= u;
            P[i] = std::exp(-r[i]*delta_t)*(p_down*P[i] + p_up*P[i+1]);
            C[i] = std::max(P[i] - K, std::exp(-r[i]*delta_t)*(p_up*C[i+1] + p_down*C[i]));
        }
    }
    return C[0];
}
