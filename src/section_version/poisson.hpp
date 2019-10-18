#ifndef POISSON_H
#define POISSON_H

// Solve Poisson's equation for a rectangular box with Dirichlet
// boundary conditions on each face.
#include <stdlib.h>
#include <stdio.h>
#include <omp.h>
#define oneOsix 1/6
#define Vbound 0

int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       unsigned int xsize,  unsigned int ysize, unsigned int zsize,
                       double delta, unsigned int numiters, unsigned int numcores);
                       
int matIndex(unsigned int i, unsigned int j, unsigned int k, unsigned int xsize, unsigned int ysize);
static inline double getJ(double * __restrict__ source, double *__restrict__ potential,
		   unsigned int index,unsigned int xsize,  unsigned int ysize,
		   unsigned int zsize, double delta);
#endif
