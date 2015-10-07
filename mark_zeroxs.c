#include "mark_zeroxs.h"

/* This is written so that it may be called in blocks.
 * x is the signal whose zero crossings you want to find
 * N is the length of x
 * uc is the container for the upward crossings if MZX_GROUP_CROSSINGS is set and
 * MZX_SEARCH_BACKWARD is set. Not written to if its value is NULL. This allows
 * one to only search for downward crossings.
 * dc is the container for the downward crossings if MZX_GROUP_CROSSINGS is set,
 *  whereby uc will be the container for the upward crossings. If
 *  MZX_SEARCH_BACKWARD is set but MZX_GROUP_CROSSINGS is not set then all the
 *  crossings will be put in this array. Not written to if its value is NULL. This allows
 * one to only search for upward crossings.
 * side is the side to start on. 1 is the positive side, 0 the negative.
 * x_l is the last non-zero sample of the previous, if run for the first time,
 *  set this to x
 * maxnc is the maximum number of crossings to find. Once this many have been
 *  found, the function returns.
 * opt can contain a bitwise-or of the following defines
 *   MZX_GROUP_CROSSINGS -> groups crossings into two sets as explained above,
 *    dc must be a valid array.
 *   MZX_NO_FINAL_NULL   -> doesn't set the final index of uc and dc to NULL.
 *   MZX_SEARCH_BACKWARD -> assumes x is a pointer to the last address of an
 *                          array and searches backward for zero-crossings. Note
 *                          that when going backward, what would have been an
 *                          upward going zero-crossing is now a downward going
 *                          zero-crossing. This is compensated for so that the
 *                          upward going and downward going zero crossing
 *                          containers always contain addresses that would be
 *                          classified as upward or downward going in the
 *                          positive direction. For example, if searching
 *                          backward, the next sample looked at is positive and
 *                          the previous sample looked at was negative, this
 *                          looks like an upward going zero crossing, but when
 *                          searching in the positive direction this would have
 *                          been classified as a negative going zero crossing.
 *                          This will be classified as a negative going zero
 *                          crossing even when we are searching backward.
 * the uc and dc containers must be large enough to hold all the zero crossings. */
void mark_zeroxs(double *x, size_t N, double **uc, double **dc, int side,
        double *x_l, size_t maxnc, unsigned int opt)
{
	double *x_r;
	int n, nc;
    n = 0, nc = 0;
    while (1) {
		if (side == 0) {
			if (x[n] < 0.) {
				x_l = x + n;
			}
			if (x[n] > 0.) {
                /* We were on the negative side and now have moved to the
                 * positive side. If we are moving forward, this is an upward
                 * going zero-crossing. If we are moving backward this is a
                 * downward going zero-crossing. */
				x_r = x + n;
                if (opt & MZX_SEARCH_BACKWARD) {
                    if (dc) {
                        *(dc++) = x_l + (x_r - x_l) / 2;
                    }
                } else {
                    if (uc) {
                        *(uc++) = x_l + (x_r - x_l) / 2;
                    }
                }
				side = 1;
                nc++;
                if (nc >= maxnc) {
                    break;
                }
			}
		} else {
			if (x[n] > 0) {
				x_l = x + n;
			}
			if (x[n] < 0.) {
                /* We were on the positive side and now have moved to the
                 * negative side. If we are moving forward, this is a downward
                 * going zero-crossing. If we are moving backward, this is an
                 * upward going zero-crossing. */
				x_r = x + n;
                if (opt & MZX_GROUP_CROSSINGS) {
                    if (opt & MZX_SEARCH_BACKWARD) {
                        if (uc) {
                            *(uc++) = x_l + (x_r - x_l) / 2;
                        }
                    } else {
                        if (dc) {
                            *(dc++) = x_l + (x_r - x_l) / 2;
                        }
                    }
                } else {
                    if (opt & MZX_SEARCH_BACKWARD) {
                        if (uc) {
                            *(dc++) = x_l + (x_r - x_l) / 2;
                        }
                    } else {
                        if (dc) {
                            *(uc++) = x_l + (x_r - x_l) / 2;
                        }
                    }
                }
				side = 0;
                nc++;
                if (nc >= maxnc) {
                    break;
                }
			}
		}
        if (opt & MZX_SEARCH_BACKWARD) {
            n--;
            if (-n >= N) {
                break;
            }
        } else {
            n++;
            if (n >= N) {
                break;
            }
        }
	}
    if (opt & MZX_NO_FINAL_NULL) {
        return;
    }
    if (uc) {
        *uc = NULL; /* sentinel */
    }
    if (opt & MZX_GROUP_CROSSINGS) {
        if (dc) {
            *dc = NULL;
        }
    }
}
