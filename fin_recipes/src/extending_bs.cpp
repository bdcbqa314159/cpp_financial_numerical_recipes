#include "extending_bs.hpp"
#include "option_pricing_bs.hpp"
#include "norm_dist.hpp"
#include <cmath>

double option_price_european_call_payout(const double& S, const double &K, const double& r, const double& q, const double& sigma, const double& time){
    double sigma_2 = sigma*sigma;
    double time_sqrt = std::sqrt(time);

    double d1 = (std::log(S/K) + (r-q + 0.5*sigma_2)*time)/(sigma*time_sqrt);
    double d2 = d1-(sigma*time_sqrt);

    double call_price = S*std::exp(-q*time)*N(d1) - K*std::exp(-r*time)*N(d2);
    return call_price;
}

double option_price_european_call_dividends(const double& S, const double& K, const double& r, const double& sigma, const double& time, const v_double& dividend_times, const v_double& dividends_flows){
    double adjusted_S = S;
    for (size_t i = 0; i<dividend_times.size(); ++i){
        if (dividend_times[i]<=time)
            adjusted_S -= dividends_flows[i]*std::exp(-r*dividend_times[i]);
    }

    return option_price_call_black_scholes(adjusted_S, K, r, sigma, time);
}
