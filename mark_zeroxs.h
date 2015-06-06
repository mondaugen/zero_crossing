#ifndef MAR_ZEROXS_H
#define MAR_ZEROXS_H 
#include <stddef.h> 

#define MZX_GROUP_CROSSINGS (1 << 0)
#define MZX_NO_FINAL_NULL   (1 << 1) 
#define MZX_SEARCH_BACKWARD (1 << 2) 

void mark_zeroxs(double *x, size_t N, double **uc, double **dc, int side,
        double *x_l, size_t maxnc, unsigned int opt);

#endif /* MAR_ZEROXS_H */
