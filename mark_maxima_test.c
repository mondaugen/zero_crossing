#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mark_maxima.h" 

int main (void)
{
	size_t N = 1000;
	double x[N];
	size_t *m_maxima = (size_t*)malloc(sizeof(size_t)*N);
	size_t n;
	for (n = 0; n < N; n++) {
		x[n] = cos(2.*M_PI*n/100.);
        /* No maximum will have this index so we can see the number of maxima
         * discovered */
        m_maxima[n] = N+1;
	}
    mark_maxima(x, N, m_maxima, N);
    printf("Maxima: index, value\n");
    for (n = 0; n < N; n++) {
        if (m_maxima[n] >= N) {
            break;
        }
        printf("%lu %f\n",m_maxima[n],x[m_maxima[n]]);
    }
}

