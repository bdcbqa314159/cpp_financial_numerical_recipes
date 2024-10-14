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

double option_price_american_call_one_dividend(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& tau, c_double& D1, c_double& tau1){

    if (D1<=K*(1. -std::exp(-r*(tau-tau1))))
        return option_price_call_black_scholes(S - std::exp(-r*tau1)*D1, K, r, sigma, tau);

    c_double ACCURACY = 1.e-6;
    double sigma_square = sigma*sigma;
    double tau_sqrt = std::sqrt(tau);
    double tau1_sqrt = std::sqrt(tau1);

    double rho = -std::sqrt(tau1/tau);
    double S_bar{}, S_low{}, S_high = S;
    double c = option_price_call_black_scholes(S_high, K, r, sigma, tau-tau1);
    double temp = c-S_high-D1+K;

    while((temp>0) && (S_high<=1e10)){
        S_high*=2.;
        c = option_price_call_black_scholes(S_high, K, r, sigma, tau-tau1);
        temp = c-S_high-D1+K;
    }

    if(S_high>1e10)
        return option_price_call_black_scholes(S-D1*std::exp(-r*tau1), K, r, sigma, tau);

    S_bar = 0.5*S_high;
    c = option_price_call_black_scholes(S_bar, K, r, sigma, tau-tau1);
    temp = c-S_bar-D1+K;

    while((fabs(temp)> ACCURACY) && S_high-S_low>ACCURACY){
        if (temp < 0.) S_high = S_bar;
        else S_low = S_bar;

        S_bar = 0.5*(S_high + S_low);
        c = option_price_call_black_scholes(S_bar, K, r, sigma, tau-tau1);
        temp = c-S_bar-D1+K;
    }

    double a1 = (std::log((S-D1 * std::exp(-r * tau1)) / K) + (r + 0.5 * sigma_square) * tau) / (sigma * tau_sqrt);
    double a2 = a1 - sigma * tau_sqrt;
    double b1 = (std::log((S-D1 * std::exp(-r * tau1)) / S_bar) + (r + 0.5 * sigma_square) * tau1) / (sigma * tau1_sqrt);
    double b2 = b1 - sigma * tau1_sqrt;
    double C = (S-D1 * std::exp(-r * tau1)) * N(b1) + (S-D1 * std::exp(-r * tau1)) * N(a1,-b1, rho) - (K * std::exp(-r * tau)) * N(a2,-b2, rho) - (K-D1) * std::exp(-r * tau1) * N(b2);
    return C;
}

double futures_option_price_call_european_black(c_double& F, c_double& K, c_double& r, c_double& sigma, c_double& time){
    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(F/K) + 0.5*sigma_square*time)/(sigma*time_sqrt);
    double d2 = d1-sigma*time_sqrt;
    return std::exp(-r*time)*(F*N(d1) - K*N(d2));
}

double currency_option_price_call_european(c_double& S, c_double &K, c_double &r, c_double& r_f, c_double& sigma, c_double& time){

    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(S / K) + (r-r_f + 0.5 * sigma_square) * time) / (sigma * time_sqrt);
    double d2 = d1 - sigma*time_sqrt;

    return S*std::exp(-r_f*time)*N(d1) - K*std::exp(-r*time)*N(d2);
}

double option_price_american_perpetual_call(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma)
{
    double sigma_square = sigma*sigma;
    double h1 = 0.5 - ((r-q)/sigma_square);
    double alpha = (r - q) / sigma_square - 0.5;
    double alpha_square = alpha*alpha;

    h1 += std::sqrt(alpha_square + 2. * r / sigma_square);
    double out = (K / (h1-1.))*std::pow(((h1-1.)/h1)*(S/K), h1);
    return out;
}
