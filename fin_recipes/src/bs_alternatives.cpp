#include "bs_alternatives.hpp"
#include "option_pricing_bs.hpp"
#include <cmath>
#include <complex>
#include <gsl/gsl_integration.h>

double option_price_call_merton_jump_diffusion(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& T, c_double& lambda, c_double& kappa, c_double& delta){

    const size_t MAX_N = 50;
    double tau = T;
    double sigma_square = sigma*sigma;
    double delta_square = delta*delta;
    double lambda_prime = lambda*(1+kappa);
    double gamma = std::log(1+kappa);
    double c = std::exp(-lambda_prime*tau)*option_price_call_black_scholes(S, K, r-lambda*kappa, sigma, tau);
    double log_n = 0;
    for (size_t n = 1; n<=MAX_N; ++n){
        log_n += std::log(1.*n);
        double sigma_n = std::sqrt(sigma_square+n*delta_square/tau);
        double r_n = r - lambda*kappa+n*gamma/tau;
        c += std::exp(-lambda_prime*tau+n*std::log(lambda_prime*tau) - log_n)*option_price_call_black_scholes(S,K,r_n, sigma_n, tau);
    }
    return c;
}

struct heston_parms{
    double K, x, r, v, tau, kappa, theta, rho, sigma, lambda;
    int j;
};

extern "C"
{
    double heston_integrand_j(double phi, void *p)
    {
        struct heston_parms *parms = (struct heston_parms *)p;
        double K = (parms->K);
        double x = (parms->x);
        double v = (parms->v);
        double r = (parms->r);
        double kappa = (parms->kappa);
        double theta = (parms->theta);
        double rho = (parms->rho);
        double sigma = (parms->sigma);
        double lambda = (parms->lambda);
        double tau = (parms->tau);
        double j = (parms->j);
        double sigma_sqr = sigma*sigma;
        double uj;
        double bj;
        if (j == 1)
        {
            uj = 0.5;
            bj = kappa + lambda - rho * sigma;
        }
        else
        {
            uj =-0.5;
            bj = kappa + lambda;
        };
        std::complex<double> i(0, 1);
        double a = kappa * theta;
        std::complex<double> d = std::sqrt(std::pow(rho * sigma * phi * i-bj, 2) - sigma_sqr * (2 * uj * phi * i - std::pow(phi, 2)));
        std::complex<double> g = (bj-rho * sigma * phi * i + d) / (bj-rho * sigma * phi * i-d);
        std::complex<double> C = r * phi * i * tau + (a / sigma_sqr) * ((bj-rho * sigma * phi * i + d) * tau - 2.0 * std::log((1.0-g * std::exp(d * tau)) / (1.0-g)));
        std::complex<double> D = (bj-rho * sigma * phi * i + d) / sigma_sqr * ((1.0- std::exp(d * tau)) / (1.0-g * std::exp(d * tau)));
        std::complex<double> f1 = std::exp(C + D * v + i * phi * x);
        std::complex<double> F = std::exp(-phi * i * std::log(K)) * f1 / (i * phi);
        return real(F);
    }
};

inline double heston_Pj(double S, double K, double r, double v, double tau, double sigma,
                        double kappa, double lambda, double rho, double theta, int j)
{
    double x = std::log(S);
    struct heston_parms parms = {K, x, r, v, tau, kappa, theta, rho, sigma, lambda, j};
    size_t n = 10000;
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(n);
    gsl_function F;
    F.function = &heston_integrand_j;
    F.params = &parms;
    double result, error;
    gsl_integration_qagiu(&F, 0, 1e-7, 1e-7, n, w, &result, &error); // integral to infinity starting at zero
    return 0.5 + result/M_PI;
}

double heston_call_option_price(c_double &S, c_double &K, c_double &r, c_double &v,c_double &tau, c_double &rho, c_double &kappa,c_double &lambda, c_double &theta, c_double &sigma){

    double P1 = heston_Pj(S,K,r,v,tau,sigma,kappa,lambda,rho,theta,1);
    double P2 = heston_Pj(S, K, r, v, tau, sigma, kappa, lambda, rho, theta, 2);

    double C = S*P1-K*std::exp(-r*tau)*P2;
    return C;
}
