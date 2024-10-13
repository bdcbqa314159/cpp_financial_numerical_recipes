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
    double ones_data[] = {1, 1, 1};
    double r = 0.09;

    int size = 3;

    gsl_vector_view e = gsl_vector_view_array(e_data, 3);
    // gsl_vector_view w = gsl_vector_view_array(w_data, 3);
    gsl_vector_view ones = gsl_vector_view_array(ones_data, 3);
    gsl_matrix_view V = gsl_matrix_view_array(V_data, 3, 3);

    int s{};
    gsl_permutation *p = gsl_permutation_alloc(3);
    gsl_linalg_LU_decomp(&V.matrix, p, &s);
    gsl_matrix *V_inv = gsl_matrix_alloc(size, size);
    gsl_linalg_LU_invert(&V.matrix, p, V_inv);

    gsl_vector *V_inv_e = gsl_vector_alloc(3);
    gsl_vector *V_inv_ones = gsl_vector_alloc(3);
    gsl_blas_dgemv(CblasNoTrans, 1.0, V_inv, &e.vector, 0.0, V_inv_e);
    gsl_blas_dgemv(CblasNoTrans, 1.0, V_inv, &ones.vector, 0.0, V_inv_ones);

    double a{}, b{}, c{};

    gsl_blas_ddot(&ones.vector, V_inv_e, &a);
    gsl_blas_ddot(&e.vector, V_inv_e, &b);
    gsl_blas_ddot(&ones.vector, V_inv_ones, &c);

    double det_A = b*c - a*a;

    std::cout<<"a = "<<a<<"\n";
    std::cout<<"b = "<<b<<"\n";
    std::cout<<"c = "<<c<<"\n";

    std::cout << "det_A = " << det_A << "\n";

    gsl_vector *temp_1 = gsl_vector_alloc(3);
    gsl_vector *temp_2 = gsl_vector_alloc(3);

    gsl_vector *g = gsl_vector_alloc(3);
    gsl_vector *h = gsl_vector_alloc(3);

    gsl_vector *w = gsl_vector_alloc(3);


    gsl_vector_add(temp_1, &ones.vector);
    gsl_vector_scale(temp_1, b);

    gsl_vector_add(temp_2, &e.vector);
    gsl_vector_scale(temp_2, a);

    gsl_vector_sub(temp_1, temp_2);

    gsl_blas_dgemv(CblasTrans, 1.0, V_inv, temp_1, 0.0, g);
    gsl_vector_scale(g, 1/det_A);

    gsl_vector_set_all(temp_1, 0);
    gsl_vector_set_all(temp_2, 0);

    gsl_vector_add(temp_1, &e.vector);
    gsl_vector_scale(temp_1, c);

    gsl_vector_add(temp_2, &ones.vector);
    gsl_vector_scale(temp_2, a);

    gsl_vector_sub(temp_1, temp_2);
    gsl_blas_dgemv(CblasTrans, 1.0, V_inv, temp_1, 0.0, h);
    gsl_vector_scale(h, 1/det_A);

    gsl_vector_set_all(temp_1, 0);
    gsl_vector_set_all(temp_2, 0);

    gsl_vector_add(temp_1, h);
    gsl_vector_scale(temp_1, r);

    gsl_vector_add(w, g);
    gsl_vector_add(w, temp_1);

    printf("g = \n");
    gsl_vector_fprintf(stdout, g, "%g");

    printf("h = \n");
    gsl_vector_fprintf(stdout, h, "%g");

    printf("w = \n");
    gsl_vector_fprintf(stdout, w, "%g");

    // gsl_linalg_LU_solve(&m.matrix, p, &b.vector, d);
    // printf("d = \n");
    // gsl_vector_fprintf(stdout, d, "%g");

    // gsl_vector *Vw = gsl_vector_alloc(3);

    // double E_r{},Var_r{};

    //
    // gsl_blas_dgemv(CblasNoTrans, 1.0, &V.matrix, &w.vector, 0.0, Vw);
    // gsl_blas_ddot(&w.vector, Vw, &Var_r);

    // double sigma_r = std::sqrt(Var_r);

    // std::cout << "E(r) = " << E_r << "\n";
    // std::cout << "Var(r) = " << Var_r << "\n";
    // std::cout << "sigma(r) = " << sigma_r << "\n";

    return 0;
}
