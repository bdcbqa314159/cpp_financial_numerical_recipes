#include "bond_options.hpp"
#include "norm_dist.hpp"
#include <cmath>
#include <algorithm>

double bond_option_price_put_zero_black_scholes(c_double& B, c_double& K, c_double& r, c_double& sigma, c_double& time){
    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(B/K) + r*time)/(sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;
    double p = K*std::exp(-r*time)*N(-d2) - B*N(-d1);
    return p;
}

double bond_option_price_put_coupon_bond_black_scholes(c_double& B, c_double& K, c_double& r, c_double& sigma, c_double& time, c_v_double& coupon_times, c_v_double& coupon_flows){

    double adjusted_B = B;
    for (size_t i = 0; i<coupon_times.size(); ++i){
        if (coupon_times[i]<=time)
            adjusted_B -= coupon_flows[i]*std::exp(-r*coupon_times[i]);
    }
    return bond_option_price_put_zero_black_scholes(adjusted_B, K, r,sigma, time);
}

double bond_option_price_put_american_binomial(c_double& B, c_double& K, c_double& r, c_double& sigma, c_double& t, const size_t& steps){

    double delta_t = t/steps;
    double R = std::exp(r*delta_t);
    double Rinv = 1./R;

    double u = std::exp(sigma * std::sqrt(delta_t));
    double uu = u*u;
    double d = 1./u;
    double p_up = (R-d)/(u-d);
    double p_down = 1. - p_up;

    const size_t size_final = steps+1;
    v_double prices(size_final), put_values(size_final);

    prices[0] = B * std::pow(d, steps);
    for (size_t i = 1; i<size_final; ++i) prices[i] = uu*prices[i-1];
    for (size_t i = 0; i<size_final; ++i) put_values[i] = std::max(0., K-prices[i]);

    for (int step = steps-1; step>=0; --step){
        for (size_t i = 0; i<=step; ++i){
            put_values[i] = (p_up*put_values[i+1] + p_down*put_values[i])*Rinv;
            prices[i] = d*prices[i+1];
            put_values[i] = std::max(put_values[i], K-prices[i]);
        }
    }
    return put_values[0];
}
