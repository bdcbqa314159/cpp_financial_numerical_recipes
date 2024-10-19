#pragma once
#include "definitions.hpp"
#include "term_structure.hpp"

double term_structure_yield_nelson_siegel(c_double &t, c_double &beta0, c_double &beta1, c_double &beta2, c_double &lambda);

class term_structure_class_nelson_siegel : public term_structure_class
{
private:
    double beta0_{}, beta1_{}, beta2_{}, lambda_{};

public:
    term_structure_class_nelson_siegel() = default;
    term_structure_class_nelson_siegel(c_double &beta0, c_double &beta1, c_double &beta2, c_double &lambda);
    virtual double r(const double &t) const;
};

double term_structure_yield_svensson(c_double &t, c_double &beta0, c_double &beta1, c_double &beta2, c_double& beta3, c_double& tau1, c_double& tau2);

class term_structure_class_svensson : public term_structure_class
{
private:
    double beta0_{}, beta1_{}, beta2_{}, beta3_{}, tau1_{}, tau2_{};

public:
    term_structure_class_svensson() = default;
    term_structure_class_svensson(c_double &b0, c_double &b1, c_double &b2, c_double &b3, c_double &tau1, c_double &tau2);
    virtual double r(c_double &T) const;
};

double term_structure_discount_factor_cubic_spline(c_double& t, c_double& b1, c_double& c1, c_double& d1, c_v_double& f, c_v_double& knots);

class term_structure_class_cubic_spline: public term_structure_class{
    private:
        double b_{}, c_{}, d_{};
        v_double f_{}, knots_{};
    public:
        term_structure_class_cubic_spline() = default;
        term_structure_class_cubic_spline(c_double& b, c_double& c, c_double& d, c_v_double& f, c_v_double& knots);
        virtual double d(c_double& t) const;
};

double term_structure_discount_factor_cir(c_double &t, c_double &r, c_double &kappa, c_double &lambda, c_double &theta, c_double &sigma);

class term_structure_class_cir: public term_structure_class{

    private:
        double r_{}, kappa_{}, lambda_{}, theta_{}, sigma_{};
    public:
        term_structure_class_cir() = default;
        term_structure_class_cir(c_double& r, c_double& k, c_double& l, c_double& th, c_double& sigma);
        virtual double d(c_double& t) const;
};

double term_structure_discount_factor_vasicek(c_double &time, c_double &r, c_double &a, c_double &b, c_double &sigma);

class term_structure_class_vasicek: public term_structure_class{
    private:
        double r_{}, a_{}, b_{}, sigma_{};
    public:
        term_structure_class_vasicek() = default;
        term_structure_class_vasicek(c_double& r, c_double& a, c_double& b, c_double& sigma);
        virtual double d(c_double& t) const;
};
