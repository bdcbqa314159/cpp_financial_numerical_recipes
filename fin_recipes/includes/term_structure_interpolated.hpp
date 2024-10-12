#pragma once
#include <vector>
#include "definitions.hpp"
#include "term_structure.hpp"

class term_structure_interpolated_class: public term_structure_class{

private:
    v_double times_{}, yields_{};
    void clear();

public:
    term_structure_interpolated_class() = default;
    term_structure_interpolated_class(const v_double& times, const v_double& yields);
    virtual ~term_structure_interpolated_class() = default;
    term_structure_interpolated_class(const term_structure_interpolated_class& other) = default;
    term_structure_interpolated_class &operator=(const term_structure_interpolated_class& other) = default;

    size_t no_observations() const{ return times_.size();}
    virtual double r(const double& t) const;
    void set_interpolated_observations(const v_double& times, const v_double& yields);
};
