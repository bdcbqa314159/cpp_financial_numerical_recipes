#include "norm_dist.hpp"
#include <cmath>
#include <cstdlib>
#include <gsl/gsl_integration.h>
#include <iostream>
#include <limits>

double n(const double &z){
    return std::exp(-0.5*z*z)/std::sqrt(2*PI);
}

double N(const double &z)
{
    if (z > 6.0)
    {
        return 1.0;
    }

    double b1 = 0.31938153;
    double b2 = -0.356563782;
    double b3 = 1.781477937;
    double b4 = -1.821255978;
    double b5 = 1.330274429;
    double p = 0.2316419;
    double c2 = 0.3989423;

    double a = fabs(z);
    double t = 1.0 / (1.0 + a * p);
    double b = c2 * exp((-z) * (z / 2.0));
    double n = ((((b5 * t + b4) * t + b3) * t + b2) * t + b1) * t;
    n = 1.0-b * n;
    if (z < 0.0)
        n = 1.0 - n;
    return n;
};

inline double f(const double &x, const double &y,
                const double &aprime, const double &bprime,
                const double &rho)
{
    double r = aprime * (2 * x-aprime) + bprime * (2 * y-bprime) + 2 * rho * (x-aprime) * (y-bprime);
    return exp(r);
};

inline double sgn(const double &x)
{
    return x>=0 ? 1 : -1;
};

double N(const double &a, const double &b, const double &rho)
{
    if ((a <= 0.0) && (b <= 0.0) && (rho <= 0.0))
    {
        double aprime = a / sqrt(2.0 * (1.0-rho * rho));
        double bprime = b / sqrt(2.0 * (1.0-rho * rho));
        double A[4] = {0.3253030, 0.4211071, 0.1334425, 0.006374323};
        double B[4] = {0.1337764, 0.6243247, 1.3425378, 2.2626645};
        double sum = 0;
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                sum += A[i] * A[j] * f(B[i], B[j], aprime, bprime, rho);
            };
        };
        sum = sum * (sqrt(1.0-rho * rho) / PI);
        return sum;
    }
    else if(a * b * rho <= 0.0)
    {
        if ((a <= 0.0) && (b >= 0.0) && (rho >= 0.0))
        {
            return N(a) - N(a, -b, -rho);
        }
        else if ((a >= 0.0) && (b <= 0.0) && (rho >= 0.0))
        {
            return N(b) - N(-a, b, -rho);
        }
        else if ((a >= 0.0) && (b >= 0.0) && (rho <= 0.0))
        {
            return N(a) + N(b) - 1.0 + N(-a, -b, rho);
        };
    }

    else if (a * b * rho >= 0.0)
    {
        double denum = sqrt(a * a - 2 * rho * a * b + b * b);
        double rho1 = ((rho * a - b) * sgn(a)) / denum;
        double rho2 = ((rho * b - a) * sgn(b)) / denum;
        double delta = (1.0-sgn(a) * sgn(b)) / 4.0;
        return N(a, 0.0, rho1) + N(b, 0.0, rho2) - delta;
    }

    else
    {
        std::cout << " unknown " << std::endl;
    }

    return -1e32; // should never get here, alternatively throw exception
};

double random_uniform_0_1()
{
    return double(rand()) / double(RAND_MAX); // this uses the C library random number generator.
};

double random_normal()
{
    double U1{}, U2{}, V1{}, V2{};
    double S = 2;
    while (S >= 1)
    {
        U1 = random_uniform_0_1();
        U2 = random_uniform_0_1();
        V1 = 2.0 * U1-1.0;
        V2 = 2.0 * U2-1.0;
        S = std::pow(V1, 2) + std::pow(V2, 2);
    };
    double X1 = V1 * std::sqrt((-2.0 * std::log(S)) / S);
    return X1;
};

struct n3_parms
{
    double h;
    double k;
    double rho12;
    double rho13;
    double rho23;
};

extern "C"
{
    double f3(double z, void *p)
    {
        struct n3_parms *parms = (struct n3_parms *)p;
        double h = (parms->h);
        double k = (parms->k);

        double rho12 = (parms->rho12);
        double rho13 = (parms->rho13);
        double rho23 = (parms->rho23);
        double f = n(z);
        f *= N((k-rho23 * z) / sqrt(1.0-rho23 * rho23),
               (h-rho13 * z) / (sqrt(1.0-rho13 * rho13)),
               (rho12-rho13 * rho23) / (sqrt(1.0-rho13 * rho13) * sqrt(1.0-rho23 * rho23)));
        return f;
    }
}

double N3(const double &h, const double &k, const double &j,
          const double &rho12, const double &rho13, const double &rho23)
{
    struct n3_parms parms = {h, k, rho12, rho13, rho23};
    size_t n = 1000;
    gsl_integration_workspace *w = gsl_integration_workspace_alloc(n);
    gsl_function F;
    F.function = &f3;
    F.params = &parms;
    double result, error;
    gsl_integration_qags(&F, 20.0, j, 1e-7, 1e-7, n, w, &result, &error);
    return result;
};
