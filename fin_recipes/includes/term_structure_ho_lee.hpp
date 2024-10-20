#pragma once
#include "definitions.hpp"
#include "term_structure.hpp"
#include "bond_pricing.hpp"
#include <memory>
#include <vector>

class term_structure_class_ho_lee: public term_structure_class{
    private:
        term_structure_class* initial_term_{};
        int n_{}, i_{};
        double delta_{}, pi_{};

    public:
        term_structure_class_ho_lee() = default;
        term_structure_class_ho_lee(term_structure_class* fitted_term, const int &n, const int &i, c_double &delta, c_double &pi);
        double d(c_double& t) const;
};

std::vector<std::vector<term_structure_class_ho_lee>>
term_structure_ho_lee_build_term_structure_tree(term_structure_class *initial, const int &no_steps, c_double &delta, c_double &pi);

double price_european_call_option_on_bond_using_ho_lee(term_structure_class *initial, c_double &delta, c_double &pi, c_v_double &underlying_bond_cflow_times, c_v_double &underlying_bond_cflows, c_double &K, c_double &option_time_to_mat);

class time_contingent_cash_flows{
    public:
        v_double times{}, cash_flows{};
        time_contingent_cash_flows() = default;
        time_contingent_cash_flows(c_v_double& in_times, c_v_double& in_cflows):times(in_times), cash_flows(in_cflows){}
        inline size_t no_cflows(){return times.size();}
};

std::vector<time_contingent_cash_flows>
build_time_series_of_bond_time_contingent_cash_flows(c_v_double& initial_times, c_v_double& initial_cflows);

double price_european_call_option_on_bond_using_ho_lee(term_structure_class *initial,c_double &delta,c_double &pi, c_v_double &underlying_bond_cflow_times, c_v_double &underlying_bond_cflows, c_double &K, c_double &time_to_maturity);
