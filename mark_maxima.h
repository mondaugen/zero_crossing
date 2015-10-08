#ifndef MARK_MAXIMA_H
#define MARK_MAXIMA_H 
#include <stddef.h> 
void mark_maxima(double * const x, size_t N, double **maxima, size_t *M);
void sort_maxima(double **maxima, size_t M);
#endif /* MARK_MAXIMA_H */
