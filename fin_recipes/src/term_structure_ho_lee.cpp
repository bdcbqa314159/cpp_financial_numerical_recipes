#include "term_structure_ho_lee.hpp"

term_structure_class_ho_lee::term_structure_class_ho_lee(term_structure_class *fitted_term, const int &n, const int &i, c_double &delta, c_double &pi) : initial_term_(fitted_term), n_(n), i_(i), delta_(delta), pi_(pi)
{
}

inline double hT(c_double& T, c_double& delta, c_double& pi){
    return (1./(pi + (1-pi)*std::pow(delta, T)));
}

double term_structure_class_ho_lee::d(c_double& T) const{
    double d = (*initial_term_).d(T+n_)/(*initial_term_).d(n_);
    for (size_t j = 1; j<n_; ++j)
        d*=hT(T + (n_ - j), delta_, pi_)/hT(n_ -j, delta_, pi_);

    d *= hT(T, delta_, pi_)*std::pow(delta_, T*(n_ -i_));
    return d;
}

std::vector<std::vector<term_structure_class_ho_lee>>
term_structure_ho_lee_build_term_structure_tree(term_structure_class* initial, const int &no_steps, c_double &delta, c_double &pi)
{

    std::vector<std::vector<term_structure_class_ho_lee>> hl_tree;
    for (size_t t = 0; t<5; ++t){
        hl_tree.push_back(std::vector<term_structure_class_ho_lee>());
        for (size_t j = 0; j<=t; ++j){
            term_structure_class_ho_lee hl(initial, t, j, delta, pi);
            hl_tree[t].push_back(hl);
        }
    }

    return hl_tree;
}

std::vector<time_contingent_cash_flows>
build_time_series_of_bond_time_contingent_cash_flows(c_v_double &initial_times, c_v_double &initial_cflows)
{
    std::vector<time_contingent_cash_flows> vec_cf;
    v_double times = initial_times;
    v_double cflows = initial_cflows;

    while (times.size() > 0)
    {
        vec_cf.push_back(time_contingent_cash_flows(times, cflows));
        v_double tmp_times{}, tmp_cflows{};
        for (size_t i = 0; i < times.size(); ++i)
        {
            if (times[i] - 1. >= 0.)
            {
                tmp_times.push_back(times[i] - 1);
                tmp_cflows.push_back(cflows[i]);
            }
        }
        times = tmp_times;
        cflows = tmp_cflows;
    }
    return vec_cf;
}

double price_european_call_option_on_bond_using_ho_lee(term_structure_class *initial, c_double &delta, c_double &pi, c_v_double &underlying_bond_cflow_times, c_v_double &underlying_bond_cflows, c_double &K, c_double &time_to_maturity)
{

    int T = static_cast<int>(time_to_maturity + 0.0001);
    std::vector<std::vector<term_structure_class_ho_lee>> hl_tree = term_structure_ho_lee_build_term_structure_tree(initial, T + 1, delta, pi);
    std::vector<time_contingent_cash_flows> vec_cf = build_time_series_of_bond_time_contingent_cash_flows(underlying_bond_cflow_times, underlying_bond_cflows);

    v_double values(T + 1);
    for (size_t i = 0; i <= T; ++i)
    {
        values[i] = std::max(0., bonds_price(vec_cf[T + 1].times, vec_cf[T + 1].cash_flows, hl_tree[T + 1][i].r(i)) - K);
    }

    for (int t = T; t >= 0; --t)
    {
        v_double value_this(t + 1);
        for (size_t i = 0; i <= t; ++i)
            value_this[i] = (pi * values[i + 1] + (1. - pi) * values[i]) * hl_tree[t][i].d(1);
        values = value_this;
    }

    return values[0];
}
