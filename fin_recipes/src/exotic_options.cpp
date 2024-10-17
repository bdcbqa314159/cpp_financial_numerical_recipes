#include "exotic_options.hpp"
#include "norm_dist.hpp"
#include <algorithm>
#include <vector>

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
