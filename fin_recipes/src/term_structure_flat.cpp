#include "term_structure_flat.hpp"

term_structure_flat_class::term_structure_flat_class(const double &r) : R_(r) {}
term_structure_flat_class::~term_structure_flat_class() {};

double term_structure_flat_class::r(const double& t)const{
    return t>=0 ? R_:0;
}

void term_structure_flat_class::set_int_rate(const double& r){R_ = r;}
