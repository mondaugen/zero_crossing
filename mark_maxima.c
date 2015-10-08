#include "mark_maxima.h" 
#include <stdlib.h> 
#include "mark_zeroxs.h" 

/* Find maxima in signal x.
 * x is the signal to examine.
 * N is the length of x.
 * maxima is an array that will contain no more than N-1 pointers to maximum
 * points in x.
 * M points to a size_t that will contain the number of maxima found
 */
void mark_maxima(double * const x, size_t N, double **maxima, size_t *M)
{
    double x_diff[N-1];
    double *dc[N-1];
    size_t n;
    for (n = 0; n < (N-1); n++) {
        x_diff[n] = x[n+1]-x[n];
    }
    mark_zeroxs(x_diff,N-1,NULL,dc,1,x_diff,N-1,MZX_GROUP_CROSSINGS);
    n = 0;
    while ((dc[n] != NULL) && (n < (N-1))) {
        maxima[n] = &x[dc[n] - x_diff + 1];
        n++;
    }
    *M = n;
}

static int _compare_maxima(const void *a, const void *b)
{
    const double **ppda = (const double **)a;
    const double **ppdb = (const double **)b;
    return (**ppda < **ppdb) - (**ppda > **ppdb);
}

/* maxima is an array to maximum points
 * M is the number of elements in the array
 */
void sort_maxima(double **maxima, size_t M)
{
    qsort(maxima,M,sizeof(double*),_compare_maxima);
}
