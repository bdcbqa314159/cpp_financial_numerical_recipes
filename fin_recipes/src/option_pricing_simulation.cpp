#include "option_pricing_simulation.hpp"
#include "option_pricing_bs.hpp"
#include "norm_dist.hpp"
#include "payoffs.hpp"
#include <cmath>
#include <algorithm>


double simulate_lognormal_random_variable(c_double& S, c_double& r, c_double& sigma, c_double& time){

    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);

    double R = (r - 0.5 * sigma_square)*time;
    double SD = sigma*time_sqrt;

    return S*std::exp(R + SD*random_normal());
}

double option_price_call_european_simulated(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time, const size_t& no_sims){

    double sum_payoffs{};

    for (size_t i = 0; i<no_sims; ++i){
        double S_T = simulate_lognormal_random_variable(S,r,sigma, time);
        sum_payoffs += std::max(0., S_T - K);
    }
    return std::exp(-r*time)*(sum_payoffs/no_sims);
}

double option_price_delta_call_european_simulated(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_sims){

    double sum_payoffs{}, sum_payoffs_q{};
    double q = S*0.01;

    for (size_t i = 0; i<no_sims; ++i){

        double sigma_square = sigma * sigma;
        double time_sqrt = std::sqrt(time);

        double R = (r - 0.5 * sigma_square) * time;
        double SD = sigma * time_sqrt;

        double Z = random_normal();
        double S_T = S * std::exp(R + SD * Z);
        double S_T_q = (S+q) * std::exp(R + SD * Z);

        sum_payoffs += std::max(S_T-K,0.);
        sum_payoffs_q += std::max(S_T_q - K, 0.);
    }

    double c = std::exp(-r*time)*(sum_payoffs/no_sims);
    double c_q = std::exp(-r*time)*(sum_payoffs_q/no_sims);

    return (c_q - c)/q;
}

double derivative_price_simulate_european_generic(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims)
{
    double sum_payoffs{};
    for (size_t i = 0; i<no_sims; ++i){
        double S_T = simulate_lognormal_random_variable(S, r, sigma, time);
        sum_payoffs += pay_off(S_T, K);
    }
    return std::exp(-r*time)*(sum_payoffs/no_sims);
}

double derivative_price_simulate_european_generic_with_control_variate(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims)
{
    double c_bs = option_price_call_black_scholes(S,S,r,sigma,time);
    double sum_payoffs{},sum_payoffs_bs{};

    for (size_t n = 0; n<no_sims; ++n){
        double S_T = simulate_lognormal_random_variable(S,r,sigma, time);
        sum_payoffs+=pay_off(S_T,K);
        sum_payoffs_bs+=pay_off_call(S_T,K);
    }

    double c_sim = std::exp(-r*time)*(sum_payoffs/no_sims);
    double c_bs_sim = std::exp(-r*time)*(sum_payoffs_bs/no_sims);

    c_sim += (c_bs-c_bs_sim);

    return c_sim;

}

double derivative_price_simulate_european_generic_with_antithetic_variate(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, double pay_off(c_double &S, c_double &K), const size_t &no_sims)
{
    double sigma_square = sigma * sigma;
    double time_sqrt = std::sqrt(time);

    double R = (r - 0.5 * sigma_square) * time;
    double SD = sigma * time_sqrt;

    double sum_payoffs{};

    for (size_t i = 0; i<no_sims; ++i){
        double x = random_normal();

        double S1 = S*std::exp(R+SD*x);
        double S2 = S*std::exp(R+SD*(-x));

        sum_payoffs+=(pay_off(S1,K) + pay_off(S2,K));

    }

    return std::exp(-r*time)*(sum_payoffs/(2*no_sims));
}
