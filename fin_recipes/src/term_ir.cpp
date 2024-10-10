#include <cmath>
#include "term_ir.hpp"

double term_structure_yield_from_discount_factor(const double &d_t, const double &t){
    return -std::log(d_t) / t;
}

double term_structure_discount_factor_from_yield(const double &y, const double &t){
    return std::exp(-y * t);
}

double term_structure_forward_rate_from_yields(const double &y1, const double &y2, const double &t1, const double &t2){
    return (y2 * t2 - y1 * t1) / (t2 - t1);
}
