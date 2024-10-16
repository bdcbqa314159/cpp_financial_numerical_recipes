#pragma once

#ifndef PI
#define PI 3.14159265358979323846
#endif

double n(const double &z);
double N(const double &z);
double N(const double &a, const double &b, const double &rho);
double random_uniform_0_1();
double random_normal();
double N3(const double &h, const double &k, const double &j,
          const double &rho12, const double &rho13, const double &rho23);
