#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "mark_zeroxs.h" 

int main (void)
{
	size_t N = 1000;
	double x[N];
	double **uc;
	double **dc;
	uc = (double**)malloc(sizeof(double*)*N);
	dc = (double**)malloc(sizeof(double*)*N);
	size_t n;
	for (n = 0; n < N; n++) {
		x[n] = cos(2.*M_PI*n/100.);
	}
	printf("FORWARD DIRECTION:\n");
	printf("-----------------\n");
	mark_zeroxs(x, N, uc, dc, 1, x, N, MZX_GROUP_CROSSINGS);
	printf("Upward going zero crossings.\n");
	while (*uc != NULL) {
		printf("%ld\n",*(uc++) - x);
	}
	printf("Downward going zero crossings.\n");
	while (*dc != NULL) {
		printf("%ld\n",*(dc++) - x);
	}
	printf("BACKWARD DIRECTION:\n");
	printf("------------------\n");
	mark_zeroxs(&x[N-1], N, uc, dc, 1, &x[N-1], N,
            MZX_GROUP_CROSSINGS|MZX_SEARCH_BACKWARD);
	printf("Upward going zero crossings.\n");
	while (*uc != NULL) {
		printf("%ld\n",*(uc++) - x);
	}
	printf("Downward going zero crossings.\n");
	while (*dc != NULL) {
		printf("%ld\n",*(dc++) - x);
	}
    printf("ONLY FIND A FEW, FORWARD DIRECTION:\n");
	printf("----------------------------------\n");
	mark_zeroxs(x, N, uc, dc, 1, x, 2, MZX_GROUP_CROSSINGS);
	printf("Upward going zero crossings.\n");
	while (*uc != NULL) {
		printf("%ld\n",*(uc++) - x);
	}
	printf("Downward going zero crossings.\n");
	while (*dc != NULL) {
		printf("%ld\n",*(dc++) - x);
	}
    printf("ONLY FIND A FEW, BACKWARD DIRECTION:\n");
	printf("-----------------------------------\n");
	mark_zeroxs(&x[N-1], N, uc, dc, 1, &x[N-1], 2,
            MZX_GROUP_CROSSINGS|MZX_SEARCH_BACKWARD);
	printf("Upward going zero crossings.\n");
	while (*uc != NULL) {
		printf("%ld\n",*(uc++) - x);
	}
	printf("Downward going zero crossings.\n");
	while (*dc != NULL) {
		printf("%ld\n",*(dc++) - x);
	}
    printf("Some dumb stuff.\n");
    do {
        printf("1\n");
        printf("2\n");
        if (1) {
            if (1) {
                break;
            }
            printf("3\n");
        }
        printf("4\n");
    } while (0);
    printf("finally\n");
	return (0);
}
