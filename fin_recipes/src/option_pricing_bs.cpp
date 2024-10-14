#include "option_pricing_bs.hpp"
#include "norm_dist.hpp"
#include <cmath>

double option_price_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time){

    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(S/K) + r*time) / (sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;

    return S*N(d1) - K*std::exp(-r*time)*N(d2);
}

double option_price_delta_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time){
    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(S/K) + r*time) / (sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    return N(d1);
}

void option_price_partials_call_black_scholes(const double& S, const double& K, const double& r, const double& sigma, const double& time, double& delta, double& gamma, double& theta, double& vega, double& rho){
    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(S/K) + r*time) / (sigma*time_sqrt) + 0.5*sigma*time_sqrt;
    double d2 = d1 - sigma*time_sqrt;

    delta = N(d1);
    gamma = n(d1) / (S*sigma*time_sqrt);
    theta = -S*n(d1)*sigma / (2*time_sqrt) - r*K*std::exp(-r*time)*N(d2);
    vega = S*time_sqrt*n(d1);
    rho = K*time*std::exp(-r*time)*N(d2);
}

double option_price_implied_volatility_call_black_scholes_bisections(const double &S, const double &K, const double &r, const double &time, const double &option_price)
{
    if (option_price < 0.99 * (S - K * std::exp(-r * time)))
    {
        return 0.0;
    }

    const double ACCURACY = 1.0e-5;
    const size_t MAX_ITERATIONS = 100;
    const double HIGH_VALUE = 1.0e10;
    const double ERROR = -1e30;

    double sigma_low = 1e-5;
    double sigma_high = 0.3;
    double price = option_price_call_black_scholes(S, K, r, sigma_high, time);
    while (price < option_price)
    {
        sigma_high = 2.0 * sigma_high; // keep doubling.
        price = option_price_call_black_scholes(S, K, r, sigma_high, time);
        if (sigma_high > HIGH_VALUE)
            return ERROR; // panic, something wrong.
    };
    for (int i = 0; i < MAX_ITERATIONS; i++)
    {
        double sigma = (sigma_low + sigma_high) * 0.5;
        price = option_price_call_black_scholes(S, K, r, sigma, time);
        double test = (price-option_price);
        if (fabs(test) < ACCURACY)
        {
            return sigma;
        };
        if (test < 0.0)
        {
            sigma_low = sigma;
        }
        else
        {
            sigma_high = sigma;
        }
    };
    return ERROR;
}

double option_price_implied_volatility_call_black_scholes_newton(const double &S,
                                                                 const double &K,
                                                                 const double &r,
                                                                 const double &time,
                                                                 const double &option_price)
{
    if (option_price < 0.99 * (S-K * std::exp(-time * r)))
    { // check for arbitrage violations. Option price is too low if this happens return 0.0;
    };
    const int MAX_ITERATIONS = 100;
    const double ACCURACY = 1.0e-5;
    const double ERROR = -1e30;
    double t_sqrt = std::sqrt(time);
    double sigma = (option_price / S) / (0.398 * t_sqrt); // find initial value
    for (int i=0;i<MAX_ITERATIONS;++i){
        double price = option_price_call_black_scholes(S, K, r, sigma, time);
        double diff = option_price -price;
        if (fabs(diff) < ACCURACY)
            return sigma;
        double d1 = (std::log(S / K) + r * time) / (sigma * t_sqrt) + 0.5 * sigma * t_sqrt;
        double vega = S * t_sqrt * n(d1);
        sigma = sigma + diff / vega;
    }
return ERROR; // something screwy happened, should throw exception;
}
