#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mark_maxima.h" 

int main (int argc, char **argv)
{
	size_t N = 1000, M;
	double x[N];
	double **m_maxima = (double**)malloc(sizeof(double*)*N);
	size_t n;
    printf("Cosine, no windowing.\n");
	for (n = 0; n < N; n++) {
		x[n] = cos(2.*M_PI*n/100.);
        /* No maximum will have this address so we can see the number of maxima
         * discovered */
        m_maxima[n] = NULL;
	}
    mark_maxima(x, N, m_maxima,&M);
    printf("Maxima: index, value\n");
    for (n = 0; n < M; n++) {
        printf("%lu %f\n",m_maxima[n] - x, *m_maxima[n]);
    }
    printf("Cosine with windowing.\n");
    for (n = 0; n < N; n++) {
        double _tmp = cos(M_PI*n/1000.);
        x[n] *= (1. - _tmp*_tmp);
    }
    mark_maxima(x, N, m_maxima,&M);
    sort_maxima(m_maxima,M);
    for (n = 0; n < M; n++) {
        printf("%lu %f\n",m_maxima[n] - x, *m_maxima[n]);
    }
    if (argc > 1) {
        FILE *f = fopen(argv[1],"w");
        if (!f) {
            fprintf(stderr,"Error opening file %s.\n",argv[1]);
            return(-1);
        }
        fwrite(x,sizeof(double),N,f);
        fclose(f);
    }
    return(0);
}

