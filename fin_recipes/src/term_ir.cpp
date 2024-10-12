#include <cmath>
#include <vector>
#include "term_ir.hpp"

double term_structure_yield_from_discount_factor(const double &d_t, const double &t){
    return -std::log(d_t) / t;
}

double term_structure_discount_factor_from_yield(const double &y, const double &t){
    return std::exp(-y * t);
}

double term_structure_forward_rate_from_discount_factors(const double &d1, const double &d2, const double &t){
    return std::log(d1 / d2) / t;
}

double term_structure_forward_rate_from_yields(const double &y1, const double &y2, const double &t1, const double &t2){
    return (y2 * t2 - y1 * t1) / (t2 - t1);
}

double term_structure_yield_linearly_interpolated(const double& time, const v_double& times, const v_double& yields){

    size_t no_obs = times.size();
    if (no_obs<1) return 0;
    double t_min = times[0];
    if (time<=t_min) return yields[0];

    double t_max = times[no_obs-1];
    if (time>=t_max) return yields[no_obs-1];

    size_t t = 1;
    while( (t<no_obs) && (time>times[t])){++t;}
    double lambda = (times[t]-time)/(times[t]- times[t-1]);
    double r = yields[t-1]*lambda+yields[t]*(1. - lambda);
    return r;
}

double bonds_price(const v_double& times, const v_double& cflows, const term_structure_class& d){
    double p = 0;

    for (size_t i = 0; i<cflows.size(); ++i){
        p+=d.d(times[i])*cflows[i];
    }
    return p;
}

double bonds_duration(const v_double& times, const v_double& cflows, const term_structure_class& d){
    double S{}, D1{};

    for (size_t i = 0; i<cflows.size(); ++i){
        S+=cflows[i]*d.d(times[i]);
        D1 = cflows[i]*cflows[i]*d.d(times[i]);
    }

    return D1/S;
}

double bonds_convexity(const v_double& times, const v_double& cflows, const term_structure_class& d){
    double B{}, Cx{};
    for (size_t i = 0; i<cflows.size(); ++i){
        B+=cflows[i]*d.d(times[i]);
        Cx+=std::pow(times[i], 2)*cflows[i]*d.d(times[i]);
    }
    return Cx/B;
}
