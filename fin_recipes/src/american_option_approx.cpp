#include "american_option_approx.hpp"
#include "option_pricing_bs.hpp"
#include "extending_bs.hpp"
#include "norm_dist.hpp"
#include <cmath>
#include <algorithm>

double option_price_american_put_approximated_johnson(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time)
{

    double sigma_square = sigma*sigma;

    double a0 = 3.9649;
    double a1 = 0.032325;
    double b0 = 1.040803;
    double b1 = 0.00963;

    double gamma = 2*r/sigma_square;

    double m = (sigma_square*time)/(b0*sigma_square*time+b1);
    double Sc = K*std::pow(gamma/(gamma+1), m);
    double l = std::log(S/Sc)/std::log(K/Sc);

    double alpha = std::pow(r*time/(a0*r*time+a1), l);
    double P = alpha * option_price_put_black_scholes(S, K * std::exp(r * time), r, sigma, time) + (1 - alpha) * option_price_put_black_scholes(S,K,r,sigma, time);
    double p = option_price_put_black_scholes(S,K,r,sigma,time);
    return std::max(p,P);
}

inline double d1(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time){
    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);
    return (std::log(S/K) + (r+0.5*sigma_square*time))/(sigma*time_sqrt);
}

inline double d2(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time)
{
    double time_sqrt = std::sqrt(time);
    return d1(S,K,r,sigma,time) - sigma*time_sqrt;
}

inline double calcP2(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, c_double& t2, c_double& S2_bar, c_double& rho12){
    double P2 = K*std::exp(-r*t2)*N(-d2(S,S2_bar,r,sigma,t2));
    P2 -= S*N(-d1(S, S2_bar,r,sigma, t2));
    P2 += K * std::exp(-r * time) * N(d2(S, S2_bar, r, sigma, t2), -d2(S,K,r,sigma,time), -rho12);
    P2 -= S*N(d1(S,S2_bar,r,sigma,t2), -d1(S,K,r,sigma, time), -rho12);
    return P2;
}

double option_price_american_put_approximated_geske_johnson(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time){

    const double ACCURACY = 1e-6;
    double P1{}, P2{}, P3{};

    P1 = option_price_put_black_scholes(S,K,r,sigma,time);
    double rho12 = 1/std::sqrt(2), rho13 = 1/std::sqrt(3), rho23 = std::sqrt(2./3);
    double t2 = time/2., t23 = time*2./3, t3 = time/3.;
    double Si = S, S2_bar = S;
    double g = 1, gprime = 1;

    while (fabs(g)>ACCURACY){
        g = Si - K + option_price_put_black_scholes(Si, K, r,sigma, t2);
        gprime = 1.+option_price_delta_put_black_scholes(Si,K,r,sigma,t2);
        S2_bar = Si;
        Si = Si-g/gprime;
    }

    P2 = calcP2(S,K,r,sigma,time,t2, S2_bar, rho12);
    P2 = std::max(P1, P2);

    double S23_bar = S2_bar;

    g = 1;
    while (fabs(g)>ACCURACY){
        g = Si - K + option_price_put_black_scholes(Si, K, r,sigma, t23);
        gprime = 1. + option_price_delta_put_black_scholes(Si, K, r, sigma, t23);
        S23_bar = Si;
        Si = Si - g/gprime;
    }

    double S3_bar = S23_bar;
    g = 1;
    while (fabs(g) > ACCURACY)
    {
        g = Si - K + option_price_put_black_scholes(Si, K, r, sigma, t3);
        gprime = 1. + option_price_delta_put_black_scholes(Si, K, r, sigma, t3);
        S3_bar = Si;
        Si = Si - g / gprime;
    }

    P3 = K*std::exp(-r*t3)*N(-d2(S, S3_bar, r, sigma, t3));
    P3 -= S*N(-d1(S, S3_bar, r, sigma, t3));
    P3 += K*std::exp(-r*time)*N(d2(S, S3_bar, r, sigma, t3), -d2(S,S23_bar, r, sigma, t23), -rho12);
    P3 -= S*N(d1(S,S3_bar, r, sigma, t3), -d1(S, S23_bar, r, sigma, t23), -rho12);
    P3 += K * std::exp(-r * t23) * N3(d1(S, S3_bar, r, sigma, t3), d1(S, S23_bar, r, sigma, t23), d1(S, K, r, sigma, time), rho12, rho13, rho23);
    P3 = S * N3(d2(S, S3_bar, r, sigma, t3), d2(S, S23_bar, r, sigma, t23), d2(S, K, r, sigma, time), rho12, rho13, rho23);
    P3 = std::max(P2, P3);

    return P3 + 3.5*(P3-P2)-0.5*(P2-P1);
}

double option_price_american_call_approximated_baw(c_double& S, c_double& K, c_double& r, c_double& b, c_double& sigma, c_double& time){

    c_double ACCURACY = 1e-6;
    double sigma_square = sigma*sigma;
    double time_sqrt = std::sqrt(time);
    double nn = 2.*b/sigma_square;
    double m = 2.*r/sigma_square;
    double K1 = 1.-std::exp(-r*time);
    double nn_1_square = (nn-1)*(nn-1);
    double q2 = (-(nn - 1) + std::sqrt(nn_1_square + 4.*m/K1))*0.5;
    double q2_inf = (-(nn - 1) + std::sqrt(nn_1_square + 4. * m)) * 0.5;

    double S_star_inf = K/(1. - 1./q2_inf);
    double h2 = -(b*time+2.*sigma*time_sqrt)*(K/(S_star_inf - K));
    double S_seed = K + (S_star_inf - K)*(1. - std::exp(h2));

    size_t no_iterations = 0;
    double Si = S_seed;

    double g = 1, gprime = 1.;

    while ((fabs(g)>ACCURACY) && (fabs(gprime)>ACCURACY) && (no_iterations++<500) && (Si>0.)){
        double c = option_price_european_call_payout(Si, K, r, b, sigma, time);
        double _d1 = (std::log(Si/K) + (b+0.5*sigma_square)*time)/(sigma*time_sqrt);
        g = (1. - 1./q2)*Si - K - c + (1./q2)*Si*std::exp((b-r)*time)*N(_d1);
        gprime = (1.-1./q2)*(1.-std::exp((b-r)*time)*N(_d1)) + (1./q2)*std::exp((b-r)*time)*n(_d1)*(1./(sigma*time_sqrt));
        Si = Si - g/gprime;
    }

    double S_star = 0;
    if (fabs(g)>ACCURACY)
        S_star = S_seed;
    else
        S_star = Si;

    double C = 0;
    double c = option_price_european_call_payout(S,K,r,b,sigma,time);
    if (S>=S_star)
        C = S-K;
    else{
        double _d1 = (std::log(S_star / K) + (b + 0.5 * sigma_square) * time) / (sigma * time_sqrt);
        double A2 = (1.-std::exp((b-r)*time)*N(_d1))*S_star/q2;
        C = c+A2*std::pow(S/S_star, q2);
    }

    return std::max(C,c);
}

inline double phi(c_double& S, c_double& T, c_double& gamma, c_double& H, c_double& X, c_double& r, c_double& b, c_double& sigma){
    double sigma_square = sigma*sigma;
    double T_sqrt = std::sqrt(T);
    double kappa = 2.*b/sigma_square + 2.*gamma - 1.;
    double lambda = (-r + gamma*b + 0.5*gamma*(gamma-1.)*sigma_square)*T;
    double _d1 = - (std::log(S/H) + (b+(gamma-0.5)*sigma_square)*T)/(sigma*T_sqrt);
    double _d2 = - (std::log((X*X)/(S*H)) + (b + (gamma-0.5)*sigma_square)*T)/(sigma*T_sqrt);
    double phi = std::exp(lambda)*std::pow(S, gamma)*(N(_d1) - std::pow((X/S), kappa)*N(_d2));
    return phi;
}

double option_price_american_call_approximated_bjerksund_stensland(c_double &S, c_double &K, c_double &r, c_double &b, c_double &sigma, c_double &T){

    double sigma_square = sigma*sigma;
    double B0 = std::max(K, r*K/(r-b));
    double temp_value = (b / sigma_square - 0.5) * (b / sigma_square - 0.5);
    double beta = (0.5 - b / sigma_square) + std::sqrt(temp_value + 2. *r/sigma_square);
    double Binf = K*beta/(beta-1.);
    double hT = -(-b*T + 2.*sigma*std::sqrt(T))*((K*K)/(Binf - B0));
    double XT = B0+(Binf-B0)*(1.-std::exp(hT));

    double alpha = (XT-K)*std::pow(XT, -beta);
    double C = alpha*std::pow(S, beta);

    C -= alpha*phi(S, T, beta, XT, XT, r,b,sigma);
    C += phi(S,T,1,XT,XT, r, b,sigma);
    C -= phi(S,T,1,K,XT, r, b, sigma);
    C -= K*phi(S,T,0,XT,XT,r,b,sigma);
    C += K*phi(S,T,0,K,XT, r,b,sigma);
    double c = option_price_european_call_payout(S,K,r,b,sigma,T);
    return std::max(C,c);
}

double option_price_american_put_approximated_bjerksund_stensland(c_double &S, c_double &K, c_double &r, c_double &b, c_double &sigma, c_double &T)
{
    return option_price_american_call_approximated_bjerksund_stensland(K, S, b, r-b, sigma, T);
}
