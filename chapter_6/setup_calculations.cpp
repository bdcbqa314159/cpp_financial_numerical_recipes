#include <cmath>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <stdio.h>

int main()
{

    double e_data[] = {0.1, 0.11, 0.08};
    double V_data[] = {0.2, 0, 0,
                       0, 0.1, 0,
                       0, 0, 0.15};
    double w_data[] = {1./3, 1./3, 1./3};

    gsl_vector_view e = gsl_vector_view_array(e_data, 3);
    gsl_vector_view w = gsl_vector_view_array(w_data, 3);
    gsl_matrix_view V = gsl_matrix_view_array(V_data, 3, 3);

    gsl_vector *Vw = gsl_vector_alloc(3);

    double E_r{},Var_r{};

    gsl_blas_ddot(&w.vector, &e.vector, &E_r);
    gsl_blas_dgemv(CblasNoTrans, 1.0, &V.matrix, &w.vector, 0.0, Vw);
    gsl_blas_ddot(&w.vector, Vw, &Var_r);

    double sigma_r = std::sqrt(Var_r);

    std::cout << "E(r) = " << E_r << "\n";
    std::cout << "Var(r) = " << Var_r << "\n";
    std::cout << "sigma(r) = " << sigma_r << "\n";

    return 0;
}
