#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mark_maxima.h" 

int main (void)
{
	size_t N = 1000;
	double x[N];
	double **m_maxima = (double**)malloc(sizeof(double*)*N);
	size_t n;
	for (n = 0; n < N; n++) {
		x[n] = cos(2.*M_PI*n/100.);
        /* No maximum will have this address so we can see the number of maxima
         * discovered */
        m_maxima[n] = NULL;
	}
    mark_maxima(x, N, m_maxima, N-1);
    printf("Maxima: index, value\n");
    for (n = 0; n < N; n++) {
        if (m_maxima[n] == NULL) {
            break;
        }
        printf("%lu %f\n",m_maxima[n] - x, *m_maxima[n]);
    }
}

