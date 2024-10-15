#include "option_pricing_binomial_approx.hpp"
#include <cmath>
#include <algorithm>

double option_price_call_european_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t& steps){

    double R = std::exp(r*t/steps);
    double Rinv = 1./R;

    double u = std::exp(sigma*std::sqrt(t/steps));
    double uu = u*u;

    double d = 1./u;
    double p_up = (R-d)/(u-d);
    double p_down = 1.-p_up;

    v_double prices(steps+1);
    prices[0] = S*std::pow(d, steps);

    for (size_t i = 1; i<=steps; ++i)
        prices[i] = uu*prices[i-1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i]-K);

    for (int step = steps-1; step>=0; --step)
        for (size_t i = 0;i<=step; ++i)
            call_values[i] = (p_up*call_values[i+1] + p_down*call_values[i])*Rinv;

    return call_values[0];
}

double option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps)
{

    double R = std::exp(r * t / steps);
    double Rinv = 1./R;

    double u = std::exp(sigma * std::sqrt(t / steps));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step){
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d*prices[i+1];
            call_values[i] = std::max(call_values[i], prices[i]-K);
        }

    }

    return call_values[0];
}

double option_price_delta_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps)
{

    double R = std::exp(r * t / steps);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(t / steps));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    double delta = (call_values[1]-call_values[0])/(S*u - S*d);

    return delta;
}

void option_price_partials_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, double& delta, double& gamma, double& theta, double& vega, double& rho)
{
    v_double prices(steps + 1);
    v_double call_values(steps + 1);

    double delta_t = t/steps;

    double R = std::exp(r * delta_t);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(delta_t));
    double uu = u * u;

    double d = 1. / u;
    double dd = d * d;

    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            prices[i] = d * prices[i + 1];
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    double f22 = call_values[2];
    double f21 = call_values[1];
    double f20 = call_values[0];

    for (size_t i = 0; i<=1; ++i){
        prices[i] = d * prices[i + 1];
        call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
        call_values[i] = std::max(call_values[i], prices[i] - K);
    }

    double f11 = call_values[1];
    double f10 = call_values[0];

    prices[0] = d*prices[1];
    call_values[0] = (p_up * call_values[1] + p_down * call_values[0]) * Rinv;
    call_values[0] = std::max(call_values[0],S - K);

    double f00 = call_values[0];
    delta = (f11-f10)/(S*u-S*d);
    double h = 0.5*S*(uu-dd);

    double numerator_gamma = (f22-f21)/(S*(uu-1)) - (f21-f20)/(S*(1-dd));
    gamma = numerator_gamma / h;

    theta = (f21 - f00)/(2*delta_t);
    double diff = 0.02;

    double tmp_sigma = sigma+diff;
    double tmp_prices = option_price_call_american_binomial(S,K,r,tmp_sigma,t,steps);
    vega = (tmp_prices - f00)/diff;
    diff = 0.05;
    double tmp_r = r+diff;
    tmp_prices = option_price_call_american_binomial(S, K, tmp_r, sigma, t, steps);
    rho = (tmp_prices-f00)/diff;
    return;
}

double option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double& y, c_double &sigma, c_double &t, const size_t &steps)
{

    double R = std::exp(r * t / steps);
    double R_y = std::exp((r-y) * t / steps);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(t / steps));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R_y - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    return call_values[0];
}

double option_price_call_american_proportional_dividends_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, c_v_double& div_times, c_v_double& div_flows)
{
    if (div_times.size() == 0)
        return option_price_call_american_binomial(S,K,r,sigma,t, steps);

    double delta_t = t/steps;
    double R = std::exp(r * delta_t);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(delta_t));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    std::vector<int> div_steps(div_times.size());

    for (size_t i = 0; i<div_steps.size(); ++i)
        div_steps[i] = static_cast<int>(div_times[i]/t*steps);

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);

    for (size_t i = 0; i<div_times.size(); ++i)
        prices[0]*=(1.-div_flows[i]);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i<div_steps.size(); ++i){
            if (step == div_steps[i]){
                for (size_t j = 0; j<=step+1; ++j){
                    prices[j]*=(1./(1. -div_flows[i]));
                }
            }
        }
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    return call_values[0];
}

double option_price_call_american_discrete_dividends_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps, c_v_double &div_times, c_v_double &div_flows)
{
    if (div_times.size() == 0)
        return option_price_call_american_binomial(S, K, r, sigma, t, steps);

    int steps_before_div = static_cast<int>(div_times[0]/t*steps);

    double delta_t = t / steps;
    double R = std::exp(r * delta_t);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(delta_t));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;

    double div_amount = div_flows[0];

    v_double tmp_div_times(div_times.size() - 1);
    v_double tmp_div_flows(div_times.size() - 1);

    for (size_t i = 0; i < div_times.size()-1; ++i){
        tmp_div_flows[i] = tmp_div_flows[i+1];
        tmp_div_times[i] = tmp_div_times[i+1]-tmp_div_times[0];
    }

    v_double prices(steps_before_div + 1);
    v_double call_values(steps_before_div + 1);

    prices[0] = S * std::pow(d, steps_before_div);

    for (size_t i = 1; i <= steps_before_div; ++i)
        prices[i] = uu * prices[i - 1];

    for (size_t i = 0; i <= steps_before_div; ++i)
    {

        double value_alive = option_price_call_american_discrete_dividends_binomial(prices[i]-div_amount, K, r, sigma, t-div_times[0], steps-steps_before_div, tmp_div_times,tmp_div_flows);

        call_values[i] = std::max(value_alive, prices[i] - K);
    }

    for (int step = steps_before_div - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    return call_values[0];
}

double futures_option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &t, const size_t &steps)
{

    v_double prices(steps + 1);
    v_double call_values(steps + 1);

    double delta_t = t/steps;

    double R = std::exp(r * delta_t);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(delta_t));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R - d) / (u - d);
    double p_down = 1. - p_up;


    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    return call_values[0];
}

double ccy_option_price_call_american_binomial(c_double &S, c_double &K, c_double &r, c_double &r_f, c_double &sigma, c_double &t, const size_t &steps)
{

    double R = std::exp(r * t / steps);
    double R_f = std::exp((r - r_f) * t / steps);
    double Rinv = 1. / R;

    double u = std::exp(sigma * std::sqrt(t / steps));
    double uu = u * u;

    double d = 1. / u;
    double p_up = (R_f - d) / (u - d);
    double p_down = 1. - p_up;

    v_double prices(steps + 1);
    prices[0] = S * std::pow(d, steps);

    for (size_t i = 1; i <= steps; ++i)
        prices[i] = uu * prices[i - 1];

    v_double call_values(steps + 1);

    for (size_t i = 0; i <= steps; ++i)
        call_values[i] = std::max(0., prices[i] - K);

    for (int step = steps - 1; step >= 0; --step)
    {
        for (size_t i = 0; i <= step; ++i)
        {
            call_values[i] = (p_up * call_values[i + 1] + p_down * call_values[i]) * Rinv;
            prices[i] = d * prices[i + 1];
            call_values[i] = std::max(call_values[i], prices[i] - K);
        }
    }

    return call_values[0];
}
