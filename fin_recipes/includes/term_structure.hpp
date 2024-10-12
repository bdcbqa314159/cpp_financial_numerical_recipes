#pragma once

class term_structure_class{
    public:
    virtual double r(const double& t) const;
    virtual double d(const double& t) const;
    virtual double f(const double& t1, const double& t2) const;
    virtual ~term_structure_class();
};
