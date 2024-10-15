#include "finite_differences.hpp"
#include <algorithm>
#include <cmath>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_splinalg.h>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_vector.h>

double option_price_put_european_finite_diff_explicit(c_double& S, c_double& K, c_double& r, c_double& sigma, c_double& time, const size_t& no_S_steps, const size_t& no_t_steps){

    double sigma_square = sigma * sigma;
    size_t M = no_S_steps;
    if (M % 2 == 1)
        ++M;

    double dS = 2. * S / M;
    v_double S_values(M + 1);

    for (size_t m = 0; m <= M; ++m)
        S_values[m] = m * dS;

    size_t N = no_t_steps;
    double dt = time / N;

    v_double a(M), b(M), c(M);

    double r1 = 1. / (1. + r * dt);
    double r2 = dt / (1. + r * dt);

    for (size_t j = 1; j < M; ++j)
    {
        a[j] = r2 * 0.5 * j * (-r + sigma_square * j);
        b[j] = r1 * (1. - sigma_square * j * j * dt);
        c[j] = r2 * 0.5 * j * (r + sigma_square * j);
    }

    v_double f_next(M + 1);

    for (size_t m = 0; m <= M; ++m)
        f_next[m] = std::max(0., K - S_values[m]);

    v_double f(M + 1);
    for (int t = N - 1; t >= 0; --t)
    {
        f[0] = K;
        for (size_t m = 1; m < M; ++m)
        {
            f[m] = a[m] * f_next[m - 1] + b[m] * f_next[m] + c[m] * f_next[m + 1];
        }
        f[M] = 0;
        for (size_t m = 0; m <= M; ++m)
            f_next[m] = f[m];
    }
    return f[M / 2];
}

double option_price_put_american_finite_diff_explicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps)
{

    double sigma_square = sigma * sigma;
    size_t M = no_S_steps;
    if (M % 2 == 1)
        ++M;

    double dS = 2. * S / M;
    v_double S_values(M + 1);

    for (size_t m = 0; m <= M; ++m)
        S_values[m] = m * dS;

    size_t N = no_t_steps;
    double dt = time / N;

    v_double a(M), b(M), c(M);

    double r1 = 1. / (1. + r * dt);
    double r2 = dt / (1. + r * dt);

    for (size_t j = 1; j < M; ++j)
    {
        a[j] = r2 * 0.5 * j * (-r + sigma_square * j);
        b[j] = r1 * (1. - sigma_square * j * j * dt);
        c[j] = r2 * 0.5 * j * (r + sigma_square * j);
    }

    v_double f_next(M + 1);

    for (size_t m = 0; m <= M; ++m)
        f_next[m] = std::max(0., K - S_values[m]);

    v_double f(M + 1);
    for (int t = N - 1; t >= 0; --t)
    {
        f[0] = K;
        for (size_t m = 1; m < M; ++m)
        {
            f[m] = a[m] * f_next[m - 1] + b[m] * f_next[m] + c[m] * f_next[m + 1];
            f[m] = std::max(f[m], K-S_values[m]);
        }
        f[M] = 0;
        for (size_t m = 0; m <= M; ++m)
            f_next[m] = f[m];
    }
    return f[M / 2];
}

void iterative_inversion(gsl_spmatrix *A, gsl_vector *B, gsl_vector *F, size_t M)
{
    gsl_spmatrix *C = gsl_spmatrix_ccs(A);
    // gsl_vector *F = gsl_vector_alloc(M);

    c_double tolerance = 1e-6;
    const size_t max_iter = 10;

    const gsl_splinalg_itersolve_type *T = gsl_splinalg_itersolve_gmres;
    gsl_splinalg_itersolve *work = gsl_splinalg_itersolve_alloc(T, M, 0);
    size_t iter = 0;
    double residual;
    int status{};

    do
    {
        status = gsl_splinalg_itersolve_iterate(A, B, tolerance, F, work);

        /* print out residual norm ||A*u - f|| */
        residual = gsl_splinalg_itersolve_normr(work);
        // fprintf(stderr, "iter %zu residual = %.12e\n", iter, residual);

        if (status == GSL_SUCCESS){
            // fprintf(stderr, "Converged\n");
            continue;
        }


    } while (status == GSL_CONTINUE && ++iter < max_iter);

    return;
}

double option_price_put_american_finite_diff_implicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps)
{
    double sigma_square = sigma * sigma;
    size_t M = no_S_steps;
    if (M % 2 == 1)
        ++M;

    double dS = 2. * S / M;
    v_double S_values(M + 1);

    for (size_t m = 0; m <= M; ++m)
        S_values[m] = m * dS;

    size_t N = no_t_steps;
    double dt = time / N;

    gsl_spmatrix *A = gsl_spmatrix_alloc(M + 1, M + 1);
    gsl_vector *B = gsl_vector_alloc(M + 1);
    gsl_vector *F = gsl_vector_alloc(M + 1);

    gsl_spmatrix_set(A, 0, 0, 1.);

    for (size_t j = 1; j < M; ++j)
    {
        gsl_spmatrix_set(A, j, j - 1, 0.5 * j * dt * (r - sigma_square * j));
        gsl_spmatrix_set(A, j, j, 1. + dt * (r + sigma_square * j * j));
        gsl_spmatrix_set(A, j, j + 1, 0.5 * j * dt * (-r - sigma_square * j));
    }

    gsl_spmatrix_set(A, M, M, 1.);

    for (size_t j = 0; j <= M; ++j)
    {
        gsl_vector_set(B, j, std::max(0., K - S_values[j]));
    }

    iterative_inversion(A, B, F, M+1);

    for (int t = N - 1; t >= 0; --t)
    {
        gsl_vector_swap(B, F);

        iterative_inversion(A, B, F, M+1);

        for (size_t m = 1; m < M; ++m)
        {
            double f_m = gsl_vector_get(F,m);
            gsl_vector_set(F,m,std::max(f_m, K - S_values[m]));
        }

    }
    return gsl_vector_get(F, M/2);
}

double option_price_put_european_finite_diff_implicit(c_double &S, c_double &K, c_double &r, c_double &sigma, c_double &time, const size_t &no_S_steps, const size_t &no_t_steps)
{
    double sigma_square = sigma * sigma;
    size_t M = no_S_steps;
    if (M % 2 == 1)
        ++M;

    double dS = 2. * S / M;
    v_double S_values(M + 1);

    for (size_t m = 0; m <= M; ++m)
        S_values[m] = m * dS;

    size_t N = no_t_steps;
    double dt = time / N;

    gsl_spmatrix *A = gsl_spmatrix_alloc(M + 1, M + 1);
    gsl_vector *B = gsl_vector_alloc(M + 1);
    gsl_vector *F = gsl_vector_alloc(M + 1);

    gsl_spmatrix_set(A, 0, 0, 1.);

    for (size_t j = 1; j < M; ++j)
    {
        gsl_spmatrix_set(A, j, j - 1, 0.5 * j * dt * (r - sigma_square * j));
        gsl_spmatrix_set(A, j, j, 1. + dt * (r + sigma_square * j * j));
        gsl_spmatrix_set(A, j, j + 1, 0.5 * j * dt * (-r - sigma_square * j));
    }

    gsl_spmatrix_set(A, M, M, 1.);

    for (size_t j = 0; j <= M; ++j)
    {
        gsl_vector_set(B, j, std::max(0., K - S_values[j]));
    }

    iterative_inversion(A, B, F, M + 1);

    for (int t = N - 1; t >= 0; --t)
    {
        gsl_vector_swap(B, F);

        iterative_inversion(A, B, F, M + 1);
    }
    return gsl_vector_get(F, M / 2);
}
