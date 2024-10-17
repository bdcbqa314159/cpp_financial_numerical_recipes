#include "exotic_options.hpp"
#include "option_pricing_bs.hpp"
#include "norm_dist.hpp"
#include "option_pricing_simulation.hpp"
#include "payoffs.hpp"
#include <algorithm>
#include <vector>
#include <numeric>

double option_price_put_bermudan_binomial(c_double& S, c_double& K, c_double& r, c_double& q, c_double& sigma, c_double& time, c_v_double& potential_exercise_times, const size_t& steps){
    double delta_t = time/steps;
    double R = std::exp(r*delta_t);
    double Rinv = 1./R;
    double u = std::exp(sigma*std::sqrt(delta_t));
    double uu = u*u;
    double d = 1./u;
    double p_up = std::exp((r-q)*delta_t - d)/(u-d);
    double p_down = 1. - p_up;
    v_double prices(steps+1), put_values(steps+1);
    std::vector<int> potential_exercise_steps;
    for (size_t i = 0; i<potential_exercise_times.size(); ++i){
        double t = potential_exercise_times[i];
        if (t>0. && t<time)
            potential_exercise_steps.push_back(static_cast<int>(t/delta_t));
    }

    prices[0] = S*std::pow(d, steps);
    for (size_t i = 1; i<=steps; ++i)
        prices[i] = uu*prices[i-1];
    for (size_t i = 0; i<=steps; ++i)
        put_values[i] = std::max(0., K-prices[i]);

    for (int step = steps-1; step>=0; --step){
        bool check_exercise_this_step = false;
        for (size_t j = 0; j<potential_exercise_steps.size(); ++j){
            if (step == potential_exercise_steps[j])
                check_exercise_this_step = true;
        }

        for (size_t i = 0; i<=step; ++i){
            put_values[i] = (p_up*put_values[i+1]+p_down*put_values[i])*Rinv;
            prices[i] = d*prices[i+1];
            if (check_exercise_this_step)
                    put_values[i] = std::max(put_values[i], K-prices[i]);
        }
    }

    return put_values[0];
}

double option_price_asian_geometric_average_price_call(c_double &S, c_double &K, c_double &r, c_double &q, c_double &sigma, c_double &time){
    double sigma_square = sigma*sigma;
    double adj_div_yield = 0.5*(r+q+sigma_square/6.);
    double adj_sigma = sigma/std::sqrt(3.);
    double adj_sigma_square = adj_sigma*adj_sigma;

    double time_sqrt = std::sqrt(time);
    double d1 = (std::log(S/K) + (r-adj_div_yield+0.5*adj_sigma_square)*time)/(adj_sigma*time_sqrt);
    double d2 = d1-adj_sigma*time_sqrt;
    double call_price = S*std::exp(-adj_div_yield*time)*N(d1) - K*std::exp(-r*time)*N(d2);
    return call_price;
}

double option_price_european_lookback_call(c_double& S, c_double& Smin, c_double& r, c_double& q, c_double& sigma, c_double& time){

    if (r == q) return 0;
    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);
    double a1 = (std::log(S/Smin) + (r-q+sigma_square*0.5)*time)/(sigma*time_sqrt);
    double a2 = a1-sigma*time_sqrt;
    double a3 = (std::log(S / Smin) + (-r + q + sigma_square * 0.5) * time) / (sigma * time_sqrt);
    double Y1 = 2.*(r - q - sigma_square*0.5)*std::log(S/Smin)/sigma_square;
    return S*std::exp(-q*time)*N(a1) - S*std::exp(-q*time)*(sigma_square/(2.*(r-q)))*N(-a1) - Smin*std::exp(-r*time)*(N(a2) - sigma_square/(2.*(r-q))*std::exp(Y1)*N(-a3));
}

inline v_double simulate_lognormally_distributed_sequence(c_double& S, c_double& r, c_double& sigma, c_double& time, const size_t no_steps){
    v_double prices(no_steps);
    double delta_t = time/no_steps;
    double delta_t_sqrt = std::sqrt(delta_t);
    double sigma_square = sigma*sigma;
    double R = (r-0.5*sigma_square)*delta_t;
    double SD = sigma*delta_t_sqrt;
    double S_t = S;
    for (size_t i = 0; i<no_steps; ++i){
        S_t = S_t*std::exp(R+SD*random_normal());
        prices[i] = S_t;
    }

    return prices;
}

double derivative_price_simulate_european_option_generic(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time, double payoff(c_v_double& prices, c_double& X), const size_t &no_steps, const size_t &no_sims){
    double sum_payoffs = 0;
    for (size_t n = 0; n<no_sims; ++n){
        v_double prices = simulate_lognormally_distributed_sequence(S, r, sigma, time, no_steps);
        sum_payoffs += payoff(prices, K);
    }
    return std::exp(-r * time) * (sum_payoffs / no_sims);
}


double derivative_price_simulate_european_option_generic_with_control_variate(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time, double payoff(c_v_double& prices, c_double& X), const size_t& no_steps, const size_t& no_sims){
    double c_bs = option_price_call_black_scholes(S,S,r,sigma, time);
    double sum_payoffs{}, sum_payoffs_bs{};

    for (size_t n = 0; n<no_sims; ++n){
        v_double prices = simulate_lognormally_distributed_sequence(S,r,sigma, time, no_steps);
        double S1 = prices.back();
        sum_payoffs += payoff(prices, K);
        sum_payoffs_bs += pay_off_call(S1, S);
    }

    double c_sim = std::exp(-r*time)*(sum_payoffs/no_sims);
    double c_sim_bs = std::exp(-r*time)*(sum_payoffs_bs/no_sims);
    c_sim+=(c_bs - c_sim_bs);
    return c_sim;
}
