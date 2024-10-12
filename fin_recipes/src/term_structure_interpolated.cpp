#include "term_structure_interpolated.hpp"
#include "term_ir.hpp"

void term_structure_interpolated_class::clear(){
    times_.erase(times_.begin(), times_.end());
    yields_.erase(yields_.begin(), yields_.end());
}

term_structure_interpolated_class::term_structure_interpolated_class(const v_double& times, const v_double& yields):times_(times), yields_(yields){
}

double term_structure_interpolated_class::r(const double &t) const{
    return term_structure_yield_linearly_interpolated(t, times_, yields_);
}

void term_structure_interpolated_class::set_interpolated_observations(const v_double& times, const v_double& yields){
    clear();
    times_ = times;
    yields_ = yields;
}
