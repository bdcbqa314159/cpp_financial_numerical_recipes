#include "bond_pricing.hpp"
#include <cassert>
#include <cmath>

double bonds_price_discrete(const v_double &times, const v_double &cflows, const double &r)
{
    assert(times.size() == cflows.size());
    double pv{};
    for (size_t i = 0; i < times.size(); ++i)
        pv += cflows[i] / std::pow(1. + r, times[i]);
    return pv;
}

double bonds_yield_to_maturity(const v_double &times, const v_double &cflows, const double &bond_price){
    assert(times.size() == cflows.size());

    const double ACCURACY = 1.e-5;
    const size_t MAX_ITERATIONS = 200;

    double bot = 0, top = 1;

    while(bonds_price_discrete(times, cflows, top) > bond_price){top *= 2;}

    double r = 0.5 * (top + bot);

    for (size_t i = 0; i<MAX_ITERATIONS; ++i){
        double diff = bonds_price_discrete(times, cflows, r) - bond_price;
        if (std::fabs(diff) < ACCURACY) return r;
        if (diff > 0) bot = r;
        else top = r;

        r = 0.5 * (top + bot);
    }

    return r;
}

double bonds_duration_discrete(const v_double &times, const v_double &cflows, const double &r){

    assert(times.size() == cflows.size());
    double B = 0, D = 0;
    for (size_t i = 0; i<times.size(); ++i){
        D += times[i] * cflows[i] / std::pow(1. + r, times[i]);
        B += cflows[i] / std::pow(1. + r, times[i]);
    }

    return D / B;
}

double bonds_duration_macaulay_discrete(const v_double &times, const v_double &cflows, const double &bond_price){

    assert(times.size() == cflows.size());

    double y = bonds_yield_to_maturity(times, cflows, bond_price);
    return bonds_duration_discrete(times, cflows, y);
}

double bonds_duration_modified_discrete(const v_double &times, const v_double &cflows, const double &bond_price)
{

    assert(times.size() == cflows.size());

    double y = bonds_yield_to_maturity(times, cflows, bond_price);
    double D = bonds_duration_discrete(times, cflows, y);
    return D/(1. + y);
}

double bonds_convexity_discrete(const v_double &times, const v_double &cflows, const double &r)
{

    assert(times.size() == cflows.size());
    double Cx = 0;
    for (size_t i = 0; i<times.size(); ++i){
        Cx += cflows[i]*times[i]*(times[i] + 1) / std::pow(1. + r, times[i]);
    }

    double B = bonds_price_discrete(times, cflows, r);
    return Cx/(B * std::pow(1.+r,2));
}

double bonds_price(const v_double &times, const v_double &cflows, const double &r){

    assert(times.size() == cflows.size());
    double p = 0;
    for (size_t i = 0; i<times.size(); ++i){
        p += cflows[i] * std::exp(-r * times[i]);
    }
    return p;
}

double bonds_duration(const v_double &times, const v_double &cflows, const double &r)
{

    assert(times.size() == cflows.size());
    double S = 0, D = 0;
    for (size_t i = 0; i<times.size(); ++i){
        S += cflows[i] * std::exp(-r * times[i]);
        D += cflows[i] * times[i] * std::exp(-r * times[i]);
    }

    return D/S;
}

double bonds_duration_macaulay(const v_double &times, const v_double &cflows, const double &bond_price)
{
    assert(times.size() == cflows.size());
    double y = bonds_yield_to_maturity(times, cflows, bond_price);
    return bonds_duration(times, cflows, y);
}

double bonds_convexity(const v_double &times, const v_double &cflows, const double &r)
{
    assert(times.size() == cflows.size());
    double C = 0;

    for (size_t i = 0; i < times.size(); ++i)
    {
        C+=cflows[i]*std::pow(times[i],2)*std::exp(-r*times[i]);
    }

    double B = bonds_price(times, cflows, r);

    return C/B;
}
