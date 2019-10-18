#ifndef POISSON_H
#define POISSON_H

// Solve Poisson's equation for a rectangular box with Dirichlet
// boundary conditions on each face.
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define oneOsix 1/6

int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       int xsize,  int ysize, int zsize,
                       double delta, int numiters, int numcores);
                       
int matIndex(int i, int j, int k, int xsize, int ysize);
#endif
