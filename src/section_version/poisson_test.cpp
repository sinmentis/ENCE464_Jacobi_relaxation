/// \brief Test program for solving Poisson's equation using Jacobi relaxation
/// \author M. P. Hayes UCECE

#include <stdlib.h>
#include <stdio.h>
#include "poisson.hpp"
#include <chrono>
#include <iostream>
#include <omp.h>
using namespace std::chrono;
using namespace std;
int main (int argc, char *argv[])
{
    auto start = high_resolution_clock::now(); 
    double *source;
    double *potential;
    unsigned int N;
    unsigned int numiters;
    unsigned int numcores;    
    unsigned int xsize;
    unsigned int ysize;
    unsigned int zsize;    
    double delta = 0.1;

    if (argc < 3)
    {
        fprintf (stderr, "Usage: %s size numiters\n", argv[0]);
        return 1;
    }
    
    N = atoi(argv[1]);
    xsize = N;
    ysize = N;
    zsize = N;

    numiters = atoi(argv[2]);

    if (argc > 3)
        numcores = atoi(argv[3]);
    else
        numcores = 0;

    source = (double *)calloc(xsize * ysize * zsize, sizeof(*source));
    potential = (double *)calloc(xsize * ysize * zsize, sizeof(*potential));

    source[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2] = 1.0;    
    
    poisson_dirichlet(source, potential, xsize, ysize, zsize, delta,
                      numiters, numcores);
    auto stop = high_resolution_clock::now();
    
    auto diff = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function: "
         << diff.count()/1e6 << " seconds" << endl;
	 
    cout << "Core: "<< numcores
	 <<  " pot: " << potential[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2]
	 << endl;
	 
    free(source);
    free(potential);
    return 0;
}
