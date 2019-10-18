/// \brief Test program for solving Poisson's equation using Jacobi relaxation
/// \author M. P. Hayes UCECE

#include <stdlib.h>
#include <stdio.h>
#include "poisson.hpp"
#include <chrono>
#include <iostream>
#include <fstream>
using namespace std::chrono;
using namespace std;

#define val -1
#define FILENAME "RESULT.txt"
void inseartplaneX(double * source, unsigned int xsize, 
			unsigned int ysize, unsigned int zsize,unsigned int xVal)
{
    for(unsigned int ii = 1; ii < ysize-1; ii++){
		for(unsigned int jj = 1; jj < zsize-1; jj++){
			source[matIndex(xVal,ii,jj,xsize,ysize)] = val;
		}
    }
}

void inseartplaneY(double * source,unsigned int xsize,
		   unsigned int ysize, unsigned int zsize,unsigned int yVal)
{
    for(unsigned int ii = 1; ii < xsize-1; ii++){
		for(unsigned int jj = 1; jj < zsize-1; jj++){
			source[matIndex(ii,yVal,jj,xsize,ysize)] = val;
		}
    }
}

void inseartplaneZ(double * source,unsigned int xsize,
		   unsigned int ysize, unsigned int zVal)
{
    for(unsigned int ii = 1; ii < xsize-1; ii++){
		for(unsigned int jj = 1; jj < ysize-1; jj++){
			source[matIndex(ii,jj,zVal,xsize,ysize)] = val;
		}
    }
}

void output_result(double *potential, int xsize, int ysize, int zsize)
{
	ofstream myfile;
	myfile.open(FILENAME);
	for(int ii = 0; ii<xsize; ii++) {
		myfile << potential[matIndex(ii,xsize/2,ysize/2,xsize,ysize)] << "\n";
	}    
	myfile.close();
}

int main (int argc, char *argv[])
{
    auto start = high_resolution_clock::now(); 
    double *source;
    double *potential;
    int N;
    int numiters;
    int numcores;    
    int xsize;
    int ysize;
    int zsize;    
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
    
    /* Boundry */
	inseartplaneX(source,xsize,ysize,zsize,1);
    inseartplaneX(source,xsize,ysize,zsize,xsize-2);
    inseartplaneY(source,xsize,ysize,zsize,1);
    inseartplaneY(source,xsize,ysize,zsize,ysize-2);
	inseartplaneZ(source,xsize,ysize,1);
    inseartplaneZ(source,xsize,ysize,zsize-2);
    /* Boundry */
    
	poisson_dirichlet(source, potential, xsize, ysize, zsize, delta,
					numiters, numcores);
    auto stop = high_resolution_clock::now();
    
    auto diff = duration_cast<microseconds>(stop - start);
    
    cout << "Time taken by function: "
         << diff.count()/1e6 << " seconds" << endl;
	 
    cout << "Core: "<< numcores
	 <<  " pot: " << potential[((zsize / 2 * ysize) + ysize / 2) * xsize + xsize / 2]
	 << endl;
	
	output_result(potential, xsize, ysize, zsize);
	free(source);
	free(potential);
    return 0;
}
