#pragma once

#include "term_structure.hpp"

class term_structure_flat_class: public term_structure_class
{

private:
    double R_{};

public:
    term_structure_flat_class() = default;
    term_structure_flat_class(const double &r);
    virtual ~term_structure_flat_class();
    virtual double r(const double &t) const;
    void set_int_rate(const double &r);
};
