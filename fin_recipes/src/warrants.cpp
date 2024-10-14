#include "warrants.hpp"
#include "norm_dist.hpp"
#include "option_pricing_bs.hpp"
#include <cmath>

double warrant_price_adjusted_black_scholes(const double& S, const double &K, const double &r, const double& sigma, const double &time, const double& m, const double &n){

    double time_sqrt = std::sqrt(time);
    double w = (n/(n+m))*option_price_call_black_scholes(S, K, r, sigma, time);
    double g = w-(n/(n+m))*option_price_call_black_scholes(S+(m/n)*w, K, r, sigma, time);

    while (fabs(g)>EPSILON){
        double d1 = (std::log((S+(m/n))/K) +r*time)/(sigma*time_sqrt)+0.5*sigma*time_sqrt;
        double g_prime = 1-(m/n)*N(d1);
        w = w - g/g_prime;
        g = w-(n/(n+m))*option_price_call_black_scholes(S+(m/n)*w, K, r, sigma, time);
    }

    return w;
}
