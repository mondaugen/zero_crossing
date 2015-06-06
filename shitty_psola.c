#include <stdlib.h>
#include <stdio.h> 
#include <sndfile.h>
#include <math.h>

#include "mark_zeroxs.h"

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr,"Usage:\n\t%s soundfile factor.\n",argv[0]);
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
    double *x = (double*)malloc(sizeof(double) * sfinfo.frames);
    if (sf_read_double(sndfile, x, sfinfo.frames) < sfinfo.frames) {
        fprintf(stderr,"Error reading soundfile data.\n");
        return -1;
    }
    double **zc = (double**)malloc(sizeof(double*) * sfinfo.frames);
    int factor = atoi(argv[2]);
    mark_zeroxs(x, sfinfo.frames, zc, NULL, 1, x, 0);
    /* save each section twice */
    while (zc[1]) {
        int n;
        for (n = 0; n < factor; n++) {
            fwrite(*zc, sizeof(double), zc[1] - zc[0], stdout);
        }
        zc++;
    }
    return 0;
}

