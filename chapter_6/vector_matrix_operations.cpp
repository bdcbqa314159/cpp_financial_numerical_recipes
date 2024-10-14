#include <gsl/gsl_blas.h>
#include <stdio.h>

int main(void)
{
    double a_[] = {
        2, 1,
        1, 2};

    double b_[] = {2, 3};

    double c_[] = {0, 0};

    gsl_matrix_view A = gsl_matrix_view_array(a_, 2, 2);
    gsl_vector_view b = gsl_vector_view_array(b_, 2);
    gsl_vector_view c = gsl_vector_view_array(c_, 2);

    gsl_blas_dgemv(CblasNoTrans, 1.0, &A.matrix, &b.vector, 0.0, &c.vector);

    // gsl_blas_dgemm(CblasNoTrans, CblasNoTrans,
    //                1.0, &A.matrix, &B.matrix,
    //                0.0, &C.matrix);

    // printf("[ %g, %g\n", c[0], c[1]);
    // printf("  %g, %g ]\n", c[2], c[3]);

    gsl_vector_fprintf(stdout, &c.vector, "%g");

    return 0;
}
