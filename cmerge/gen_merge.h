#pragma once 

typedef int (*xcmp_t)(void *lhs, int lsz, void *rhs, int rsz);

int cmp_int(void *lhs, int lsz, void *rhs, int rsz);

void assign(char *parr, int *pom, char *rhs, int size);

void merge(void *mem, void *m, int *sizes, int *s, int nelts, xcmp_t cmp);

void xmsort(void *mem, int *sizes, int nelts, xcmp_t cmp);