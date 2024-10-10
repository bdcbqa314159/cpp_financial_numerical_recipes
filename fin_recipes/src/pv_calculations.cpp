#include "pv_calculations.hpp"

double cash_flow_pv_discrete(const v_double &cflow_times, const v_double &cflow_amounts, const double &r)
{

    assert(cflow_amounts.size() == cflow_amounts.size());

    double pv{};
    for (size_t i = 0; i < cflow_times.size(); ++i)
        pv += cflow_amounts[i] / std::pow(1. + r, cflow_times[i]);

    return pv;
}

double cash_flow_pv(const v_double &cflow_times, const v_double &cflow_amounts, const double &r)
{
    assert(cflow_times.size() == cflow_amounts.size());

    double pv{};
    for (size_t i = 0; i < cflow_times.size(); ++i)
        pv += cflow_amounts[i] * std::exp(-r * cflow_times[i]);
    return pv;
}

double cash_flow_irr_discrete(const v_double &cflow_times, const v_double &cflow_amounts)
{
    assert(cflow_times.size() == cflow_amounts.size());

    const double ACCURACY = 1.e-5;
    const size_t MAX_ITERATIONS = 50;

    double x1{}, x2{0.2};

    double f1 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1);
    double f2 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x2);

    for (size_t i = 0; i < MAX_ITERATIONS; ++i)
    {
        if (f1 * f2 < 0)
            break;
        if (fabs(f1) < fabs(f2))
            f1 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1 += 1.6 * (x1 - x2));
        else
            f2 = cash_flow_pv_discrete(cflow_times, cflow_amounts, x2 += 1.6 * (x2 - x1));
    }

    if (f2 * f1 > 0)
        return ERROR;
    double f = cash_flow_pv_discrete(cflow_times, cflow_amounts, x1);
    double rtb{}, dx{};
    if (f < 0)
    {
        rtb = x1;
        dx = x2 - x1;
    }
    else
    {
        rtb = x2;
        dx = x1 - x2;
    }

    for (size_t i = 0; i < MAX_ITERATIONS; ++i)
    {
        dx *= 0.5;
        double x_mid = rtb + dx;
        double f_mid = cash_flow_pv_discrete(cflow_times, cflow_amounts, x_mid);
        if (f_mid <= 0)
            rtb = x_mid;
        if ((fabs(f_mid) < ACCURACY) || (fabs(dx) < ACCURACY))
            return x_mid;
    }
    return ERROR;
}

bool cash_flow_unique_irr(const v_double &cflow_times, const v_double &cflow_amounts)
{
    assert(cflow_times.size() == cflow_amounts.size());
    int sign_changes{};

    for (size_t i = 1; i < cflow_times.size(); ++i)
    {
        if (sgn(cflow_amounts[i - 1] != sgn(cflow_amounts[i])))
            sign_changes++;
    }

    if (sign_changes == 0)
        return false;
    if (sign_changes == 1)
        return true;

    double A = cflow_amounts[0];
    sign_changes = 0;
    for (size_t i = 1; i < cflow_times.size(); ++i)
        if (sgn(A) != sgn(A += cflow_amounts[i]))
            sign_changes++;

    if (sign_changes <= 1)
        return true;
    return false;
}
