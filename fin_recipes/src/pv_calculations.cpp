#include "pv_calculations.hpp"

double cash_flow_pv_discrete(const std::vector<double> &cflow_times, const std::vector<double> &cflow_amounts, const double &r)
{

    assert(cflow_amounts.size() == cflow_amounts.size());

    double pv{};
    for (size_t i = 0; i < cflow_times.size(); ++i)
        pv += cflow_amounts[i] / std::pow(1. + r, cflow_times[i]);

    return pv;
}

double cash_flow_pv(const std::vector<double> &cflow_times, const std::vector<double> &cflow_amounts, const double &r)
{
    assert(cflow_times.size() == cflow_amounts.size());

    double pv{};
    for (size_t i = 0; i < cflow_times.size(); ++i)
        pv += cflow_amounts[i] * std::exp(-r * cflow_times[i]);
    return pv;
}