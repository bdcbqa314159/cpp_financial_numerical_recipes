#include <cmath>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <stdio.h>
int main()
{
    double a_data[] = {
        100, 0, 0, 0, 0, 0,
        0, 100, 0, 0, 0, 0,
        0, 0, 100, 0, 0, 0,
        10, 10, 10, 110, 0, 0,
        8, 8, 8, 8, 108, 0,
        9, 9, 9, 9, 9, 109};

    double b_data[] = {96, 94, 92, 118, 109, 112};
    gsl_matrix_view m = gsl_matrix_view_array(a_data, 6, 6);
    gsl_vector_view b = gsl_vector_view_array(b_data, 6);
    gsl_vector *d = gsl_vector_alloc(6);
    int s{};
    gsl_permutation *p = gsl_permutation_alloc(6);
    gsl_linalg_LU_decomp(&m.matrix, p, &s);
    gsl_linalg_LU_solve(&m.matrix, p, &b.vector, d);
    printf("d = \n");
    gsl_vector_fprintf(stdout, d, "%g");

    double t[] = {0.5, 1., 1.5, 2., 3., 4.};
    double r[] = {0, 0, 0, 0, 0, 0};

    for (int i = 0; i < 6; ++i)
        r[i] = std::pow(gsl_vector_get(d, i), -1. / t[i]) - 1;

    std::cout << "t = ";
    for (int i = 0; i < 6; ++i)
    {
        std::cout << t[i] << ", ";
    }
    std::cout << "\n";

    std::cout << "r = ";
    for (int i = 0; i < 6; ++i)
    {
        std::cout << r[i] << ", ";
    }
    std::cout << "\n";

    gsl_permutation_free(p);
    gsl_vector_free(d);
    return 0;
}
