#include "trinomial_trees.hpp"
#include <vector>
#include <cmath>

double option_price_put_american_trinomial(c_double& S, c_double& K, c_double & r, c_double& q, c_double& sigma, c_double& t, const size_t steps){

    double delta_t = t/steps;
    double R = std::exp(r*delta_t);
    double Rinv = 1./R;

    double sigma_square = sigma*sigma;

    double u = std::exp(sigma*std::sqrt(3.*delta_t));
    double d = 1./u;

    double p_u = 1./6 + std::sqrt(delta_t/(12*sigma_square))*(r-q-0.5*sigma_square);
    double p_m = 2./3;
    double p_d = 1. / 6 - std::sqrt(delta_t / (12 * sigma_square)) * (r - q - 0.5 * sigma_square);

    std::vector<v_double> Stree;
    v_double Svec;
    Svec.push_back(S);

    for (size_t step = 1; step<=steps; ++step){
        Stree.push_back(Svec);
        Svec.insert(Svec.begin(), Svec[0]*d);
        Svec.push_back(Svec[Svec.size() -1]*u);
    }

    size_t m = Svec.size();
    v_double values_next = v_double(m);
    for (size_t i = 0; i<m; ++i) values_next[i] = std::max(0., K-Svec[i]);
    v_double values;

    for (int step = steps-1; step>=0; --step){
        m = Stree[step].size();
        values = v_double(m);

        for (size_t i = 0; i<m; ++i){
            values[i] = (p_u*values_next[i+2] + p_m*values_next[i+1] + p_d*values_next[i])*Rinv;
            values[i] = std::max(values[i], K-Stree[step][i]);
        }
        values_next = values;
    }

    return values[0];
}
