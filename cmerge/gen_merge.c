#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "gen_merge.h"

int cmp_int(void *lhs, int lsz, void *rhs, int rsz)
{
    int const *lhsi = (int const *) lhs;
    int const *rhsi = (int const *) rhs;
    if (*lhsi < *rhsi)
        return 1;
    else
        return 0;
}

void assign(char *parr, int *pom, char *rhs, int size)
{
    for (int i = 0; i < size; i++) {
        //assert((i+(*pom)) < 40);
        parr[i + (*pom)] = rhs[i];
    }
    *pom += size;
}

void merge(void *mem, void *m, int *sizes, int *s, int nelts, xcmp_t cmp)
{
    char *i = (char *) mem;
    char *j = (char *) m;
    int ki = 0;
    int kj = 0;

    int kol = 0;
    char *max = (char *) mem;
    char *parr;
    int pom = 0;
    for (int g = 0; g < nelts; g++) {
        kol += sizes[g];
        max += sizes[g] * sizeof(char);
    }

    parr = calloc(kol, sizeof(char));


    // max указывает прям на конец массива

    for (int k = 0; k < nelts; k++) {
        if ((i < (char *) m) && (j < max)) {
            if (cmp(i, sizes[ki], j, s[kj]) > 0) {
                assign(parr, &pom, i, sizes[ki]);
                i = i + sizes[ki];
                ki++;
            } else {
                assign(parr, &pom, j, s[kj]);
                j = j + s[kj];
                kj++;
            }
        } else {
            if (i < (char *) m) {
                assign(parr, &pom, i, sizes[ki]);
                i = i + sizes[ki];
                ki++;
            } else {
                assign(parr, &pom, j, s[kj]);
                j = j + s[kj];
                kj++;
            }
        }
    }

    i = (char *) mem;
    for (int u = 0; u < kol; u++)
        i[u] = parr[u];

    free(parr);
}

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp)
{
    char *m = (char *) mem;
    int *s = sizes + nelts / 2;

    for (int g = 0; g < nelts / 2; g++)
        m += sizes[g];
    if (nelts <= 1)
        return;
    xmsort(mem, sizes, nelts / 2, cmp);
    xmsort((void *) m, s, (nelts + 1) / 2, cmp);        
    merge(mem, (void *) m, sizes, s, nelts, cmp);
}
