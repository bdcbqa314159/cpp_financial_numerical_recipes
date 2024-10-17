#include "generic_binomial.hpp"
#include <cmath>
#include <algorithm>
#include <vector>

double option_price_call_american_binomial(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& t, const size_t &steps){
    double R = std::exp(r*t/steps);
    double Rinv = 1./R;
    double u = std::exp(sigma*std::sqrt(t/steps));
    double d = 1./u;
    double p_up = (R-d)/(u-d);
    double p_down = 1.-p_up;

    v_double prices(steps+1);
    prices[0] = S*std::pow(d, steps);
    double uu = u*u;
    for (size_t i = 1; i<=steps; ++i) prices[i] = uu*prices[i-1];
    v_double call_values(steps+1);
    for (size_t i = 0; i<=steps; ++i) call_values[i] = std::max(0., prices[i]-K);

    for (int step = steps-1; step>=0; --step){
        for (size_t i = 0; i<=step; ++i){
            call_values[i] = (p_up*call_values[i+1] + p_down*call_values[i])*Rinv;
            prices[i] = d*prices[i+1];
            call_values[i] = std::max(call_values[i], prices[i]-K);
        }
    }

    return call_values[0];
}

double option_price_generic_binomial(c_double &S, c_double &K, double generic_payoff(c_double& S, c_double& K),c_double &r, c_double &sigma, c_double &t, const size_t &steps)
{
    double R = std::exp(r * t / steps);
    double Rinv = 1. / R;
    double u = std::exp(sigma * std::sqrt(t / steps));
    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);
    double uu = u * u;
    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];
    v_double values(steps + 1);
    for (size_t i = 0; i <= steps; ++i)
        values[i] = generic_payoff(prices[i], K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            values[i] = (p_up * values[i + 1] + p_down * values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            values[i] = std::max(values[i], generic_payoff(prices[i], K));
        }
    }

    return values[0];
}

double option_price_delta_generic_binomial(c_double &S, c_double &K, double generic_payoff(c_double &S, c_double &K), c_double &r, c_double &sigma, c_double &t, const size_t &steps)
{
    double R = std::exp(r * t / steps);
    double Rinv = 1. / R;
    double u = std::exp(sigma * std::sqrt(t / steps));
    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);
    double uu = u * u;
    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];
    v_double values(steps + 1);
    for (size_t i = 0; i <= steps; ++i)
        values[i] = generic_payoff(prices[i], K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            values[i] = (p_up * values[i + 1] + p_down * values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            values[i] = std::max(values[i], generic_payoff(prices[i], K));
        }
    }

    double delta = (values[1]-values[0])/(S*u - S*d);
    return delta;
}
