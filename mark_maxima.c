#include "mark_maxima.h" 
#include <stdlib.h> 
#include "mark_zeroxs.h" 

/* Find M maxima in signal x.
 * x is the signal to examine.
 * N is the length of x.
 * m_maxima is an array that will contain pointers to maximum points in x.
 * M is the number of maxima to find. */
void mark_maxima(double *x, size_t N, double **m_maxima, size_t M)
{
    double x_diff[N-1];
    double *dc[N-1];
    size_t n;
    for (n = 0; n < (N-1); n++) {
        x_diff[n] = x[n+1]-x[n];
    }
    mark_zeroxs(x_diff,N-1,NULL,dc,1,x_diff,N-1,MZX_GROUP_CROSSINGS);
    /* This doesn't yet sort them, just outputting them to test. */
    n = 0;
    while ((dc[n] != NULL) && (n < M)) {
        m_maxima[n] = &x[dc[n] - x_diff + 1];
        n++;
    }
}
