#include "ir_trees.hpp"
#include <cmath>

std::vector<v_double> interest_rate_trees_gbm_build(c_double& r0, c_double& u, c_double& d, const size_t n){

    std::vector<v_double> tree;
    v_double r(1);
    r[0] = r0;
    tree.push_back(r);

    for (size_t i = 1; i<=n; ++i){
        double r_top = r[r.size()-1]*u;
        for (size_t j = 0; j<i; ++j)
            r[j] = d*r[j];

        r.push_back(r_top);
        tree.push_back(r);
    }
    return tree;
}

double interest_rate_trees_gbm_value_of_cashflows(c_v_double& cflow, const std::vector<v_double>& r_tree, c_double& q){
    size_t n = cflow.size();
    std::vector<v_double> values(n);
    v_double value(n);
    for (size_t i = 0; i<n; ++i) value[i]=cflow[n-1];
    values[n-1] = value;

    for (int i = n-1; i>0; --i){
        v_double value(i, 0.);
        for (size_t j = 0; j<i; ++j)
            value[j] = cflow[i-1] + std::exp(-r_tree[i-1][j])*(q*values[i][j] + (1-q)*values[i][j+1]);

        values[i-1] = value;
    }

    return values[0][0];
}

double interest_rate_trees_gbm_value_of_callable_bond(c_v_double &cflow, const std::vector<v_double> &r_tree, c_double &q, const size_t &first_call_time, c_double& call_price)
{
    size_t n = cflow.size();
    std::vector<v_double> values(n);
    v_double value(n);
    for (size_t i = 0; i < n; ++i)
        value[i] = cflow[n - 1];
    values[n - 1] = value;

    for (int i = n - 1; i > 0; --i)
    {
        v_double value(i, 0.);
        for (size_t j = 0; j < i; ++j){
            value[j] = cflow[i - 1] + std::exp(-r_tree[i - 1][j]) * (q * values[i][j] + (1 - q) * values[i][j + 1]);
            if (i>=first_call_time)
                value[j] = std::min(value[j], call_price);
        }

        values[i - 1] = value;
    }

    return values[0][0];
}
