#include "binomial_option_pricing.hpp"
#include <cmath>
#include <algorithm>

double option_price_call_euro_binomial_single_period(const double &S, const double &K, const double &r, const double &u, const double &d){
    double q_u = (std::exp(r) - d) / (u - d);
    double q_d = 1 - q_u;

    double call_u = std::max(0.0, u*S - K);
    double call_d = std::max(0.0, d*S - K);

    return std::exp(-r)*(q_u*call_u + q_d*call_d);
}

std::vector<std::vector<double>> binomial_tree(const double& S0, const double& u, const double& d, const size_t no_steps){

    std::vector<std::vector<double>> tree(no_steps+1, std::vector<double>(no_steps+1));

    for (size_t i = 0; i <= no_steps; ++i){
        for (size_t j = 0; j <= i; ++j){
            tree[i][j] = S0*std::pow(u, j)*std::pow(d, i-j);
        }
    }

    return tree;
}

double option_price_call_euro_binomial_multi_period_given_ud(const double &S0, const double& K, const double &r, const double &u, const double &d, const size_t no_periods){

    double R_inv = std::exp(-r);
    double uu = u*u;
    double q_u = (std::exp(r) - d) / (u - d);
    double q_d = 1 - q_u;

    std::vector<double> prices(no_periods+1);
    prices[0] = S0*std::pow(d, no_periods);

    for (size_t i = 1; i <= no_periods; ++i){
        prices[i] = uu*prices[i-1];
    }

    std::vector<double> call_values(no_periods+1);

    for( size_t i = 0; i <= no_periods; ++i){
        call_values[i] = std::max(0.0, prices[i] - K);
    }

    for (int step = no_periods-1; step >= 0; --step){ //size_t is very dangerous here
        for (size_t i = 0; i <= step; ++i){
            call_values[i] = R_inv*(q_u*call_values[i+1] + q_d*call_values[i]);
        }
    }

    return call_values[0];
}
