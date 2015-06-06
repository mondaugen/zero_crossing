#include <stdlib.h>
#include <stdio.h> 
#include <sndfile.h>
#include <math.h>
#include <string.h> 

#include "mark_zeroxs.h"

int main(int argc, char **argv)
{
    if (argc != 4) {
        fprintf(stderr,"Usage:\n\t%s soundfile factor skip.\n",argv[0]);
        return -1;
    }
    /* Load soundfile */
    SF_INFO sfinfo;
    SNDFILE *sndfile;
    sndfile = sf_open(argv[1], SFM_READ, &sfinfo);
    if (!sndfile) {
        fprintf(stderr,"Error reading soundfile %s\n",argv[1]);
        return -1;
    }
    if (sfinfo.channels != 1) {
        fprintf(stderr,"Mono files only.\n");
        return -1;
    }
    int skip = atoi(argv[3]);
    double *x = (double*)malloc(sizeof(double) * sfinfo.frames);
    if (sf_read_double(sndfile, x, sfinfo.frames) < sfinfo.frames) {
        fprintf(stderr,"Error reading soundfile data.\n");
        return -1;
    }
    double **uc = (double**)malloc(sizeof(double*) * (sfinfo.frames + skip));
    double **dc = (double**)malloc(sizeof(double*) * (sfinfo.frames + skip));
    memset(uc,0,sizeof(double*) * (sfinfo.frames + skip));
    memset(dc,0,sizeof(double*) * (sfinfo.frames + skip));
    double factor = atof(argv[2]);
    mark_zeroxs(x, sfinfo.frames, uc, dc, 1, x, MZX_GROUP_CROSSINGS);
    double *y = (double*)malloc(sizeof(double) * (size_t)(sfinfo.frames / factor));
    memset(y, 0, sizeof(double) * (size_t)(sfinfo.frames / factor));
    int k; /* offset */
    double n = 0;
    while (uc[skip]) {
        int M;
        M = (uc[skip] - uc[0]);
        while (n < 1.) {
            int m;
            for (m = 0; m < M; m++) {
                y[k + m] += (*uc)[m] ;//* (cos(2. * M_PI * (((double)m)/((double)M) - 0.5)) + 1.) * 0.5;
            }
            k += M / 2;
            n += factor;
        }
        uc += skip;
        n -= 1;
    }
    fwrite(y, sizeof(double), (size_t)(sfinfo.frames / factor), stdout);
    return 0;
}

