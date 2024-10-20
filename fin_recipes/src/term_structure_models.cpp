#include "term_structure_models.hpp"
#include "norm_dist.hpp"
#include <cmath>

double term_structure_yield_nelson_siegel(c_double& t, c_double& beta0, c_double& beta1, c_double& beta2, c_double& lambda){
    if (t == 0.) return beta0;

    double t1 = t/lambda;
    double r = beta0 + (beta1+beta2)*(1-std::exp(-t1))/t1 + beta2*std::exp(-t1);
    return r;
}

term_structure_class_nelson_siegel::term_structure_class_nelson_siegel(c_double &beta0, c_double &beta1, c_double &beta2, c_double &lambda):beta0_(beta0), beta1_(beta1), beta2_(beta2), lambda_(lambda){

}

double term_structure_class_nelson_siegel::r(const double& t) const{
    if (t<=0.) return beta0_;
    return term_structure_yield_nelson_siegel(t, beta0_, beta1_, beta2_, lambda_);
}

double term_structure_yield_svensson(c_double &t, c_double &beta0, c_double &beta1, c_double &beta2, c_double& beta3, c_double& tau1, c_double& tau2){

    if (t == 0.) return beta0;
    double r = beta0;
    double t_tau1 = t/tau1, t_tau2 = t/tau2;
    r += beta1 * (1-std::exp(-t_tau1))/t_tau1;
    r += beta2 * ( (1-std::exp(-t_tau1))/t_tau1 - std::exp(-t_tau1) );
    r += beta3 * ( (1 - std::exp(-t_tau2)) / t_tau2 - std::exp(-t_tau2) );
    return r;
}

term_structure_class_svensson::term_structure_class_svensson(c_double &b0, c_double &b1, c_double &b2, c_double &b3, c_double &tau1, c_double &tau2) :beta0_(b0), beta1_(b1), beta2_(b2), beta3_(b3), tau1_(tau1), tau2_(tau2){

}

double term_structure_class_svensson::r(c_double& t) const{
    if (t<=0.) return beta0_;
    return term_structure_yield_svensson(t, beta0_, beta1_, beta2_, beta3_, tau1_, tau2_);
}

double term_structure_discount_factor_cubic_spline(c_double& t, c_double& b1, c_double& c1, c_double& d1, c_v_double& f, c_v_double& knots){
    double t2 = t*t, t3 = t2*t;
    double d = 1. + b1*t + c1*t2 + d1*t3;
    for (size_t i = 0; i<knots.size(); ++i){
        if (t>=knots[i])
            d += f[i]*std::pow(t-knots[i], 3);
        else break;
    }

    return d;
}

term_structure_class_cubic_spline::term_structure_class_cubic_spline(c_double &b, c_double &c, c_double &d, c_v_double &f, c_v_double &knots):b_(b), c_(c), d_(d), f_(f), knots_(knots){}

double term_structure_class_cubic_spline::d(c_double& t) const{
    return term_structure_discount_factor_cubic_spline(t, b_, c_, d_, f_, knots_);
}

double term_structure_discount_factor_cir(c_double& t, c_double& r, c_double& kappa, c_double& lambda, c_double& theta, c_double& sigma){
    double sigma_square = sigma*sigma;
    double kappa_plus_lambda_square = (kappa+lambda)*(kappa+lambda);
    double gamma = std::sqrt(kappa_plus_lambda_square + 2.*sigma_square);
    double denum = (gamma+kappa+lambda)*(std::exp(gamma*t) - 1) + 2.*gamma;
    double p = 2.*kappa*theta/sigma_square;

    double enum1 = 2*gamma*std::exp(0.5*(kappa+lambda+gamma)*t);
    double A = std::pow((enum1/denum), p);
    double B = (2*(std::exp(gamma*t) - 1))/denum;
    double dfact = A*std::exp(-B*r);
    return dfact;
}

term_structure_class_cir::term_structure_class_cir(c_double &r, c_double &k, c_double &l, c_double &th, c_double &sigma):r_(r), kappa_(k), lambda_(l), theta_(th), sigma_(sigma){}

double term_structure_class_cir::d(c_double& t) const{
    return term_structure_discount_factor_cir(t, r_, kappa_, lambda_, theta_, sigma_);
}

double term_structure_discount_factor_vasicek(c_double& time, c_double& r, c_double& a, c_double& b, c_double& sigma){
    double A{}, B{};
    double sigma_square = sigma*sigma;
    double aa = a*a;

    if (a == 0.){
        B = time;
        A = std::exp(sigma_square*std::pow(time, 3))/6;
    }

    else{
        B = (1. - std::exp(-a*time))/a;
        A = std::exp( (B-time)*(aa*b - 0.5*sigma_square)/aa - sigma_square*B*B*0.25/a);
    }

    double dfact = A*std::exp(-B*r);
    return dfact;
}

term_structure_class_vasicek::term_structure_class_vasicek(c_double &r, c_double &a, c_double &b, c_double &sigma):r_(r), a_(a), b_(b), sigma_(sigma){

}

double term_structure_class_vasicek::d(c_double& t) const{
    return term_structure_discount_factor_vasicek(t, r_, a_, b_, sigma_);
}

double bond_option_price_call_zero_vasicek(c_double &K, c_double &r, c_double &opt_time_to_mat, c_double &bond_time_to_mat, c_double &a, c_double &b, c_double &sigma)
{

    double T_t = opt_time_to_mat;
    double s_t = bond_time_to_mat;

    double T_s = s_t-T_t;

    double v_t_T{};
    double sigma_P{};

    if (a == 0.){
        v_t_T = sigma*std::sqrt(T_t);
        sigma_P = sigma*T_s*std::sqrt(T_t);
    }
    else{
        v_t_T = std::sqrt(sigma*sigma*(1. - std::exp(-2*a*T_t))*0.5/a);
        double B_T_s = (1. - std::exp(-a*T_s))/a;
        sigma_P = v_t_T*B_T_s;
    }

    double df_s_t = term_structure_discount_factor_vasicek(s_t,r,a,b,sigma);
    double df_T_t = term_structure_discount_factor_vasicek(T_t, r, a, b, sigma);

    double h = (1./sigma_P)*std::log(df_s_t/(df_T_t*K)) + sigma_P*0.5;
    double c = df_s_t*N(h) - K*df_T_t*N(h-sigma_P);
    return c;
}
