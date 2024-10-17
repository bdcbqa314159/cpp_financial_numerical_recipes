#include "payoffs.hpp"
#include <cmath>
#include <algorithm>
#include <numeric>

double pay_off_call(c_double &S, c_double &K)
{
    return std::max(S - K, 0.);
}

double pay_off_put(c_double &S, c_double &K)
{
    return std::max(K - S, 0.);
}

double pay_off_cash_or_nothing(c_double &S, c_double &K)
{

    return S >= K ? 1 : 0;
}

double pay_off_asset_or_nothing(c_double &S, c_double &K)
{

    return S >= K ? S : 0;
}

double pay_off_binary_call(c_double &S, c_double &K){
    return S>=K ? 1:0;
}

double pay_off_binary_put(c_double &S, c_double &K)
{
    return S <= K ? 1 : 0;
}

double payoff_arithmetic_average_call(c_v_double &prices, c_double &K)
{
    double sum = std::accumulate(prices.begin(), prices.end(), 0.);
    double avg = sum / prices.size();
    return std::max(0., avg - K);
}

double payoff_geometric_average_call(c_v_double &prices, c_double &K)
{
    double logsum = std::log(prices[0]);
    for (size_t i = 1; i < prices.size(); ++i)
        logsum += std::log(prices[i]);
    double avg = std::exp(logsum / prices.size());
    return std::max(0., avg - K);
}

double payoff_lookback_call(c_v_double &prices, c_double &unused_var)
{
    double m = *std::min_element(prices.begin(), prices.end());
    return prices.back() - m;
}

double payoff_lookback_put(c_v_double &prices, c_double &unused_var)
{
    double m = *std::max_element(prices.begin(), prices.end());
    return m - prices.back();
}
