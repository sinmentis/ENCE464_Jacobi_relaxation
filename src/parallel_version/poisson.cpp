#include "poisson.hpp"

/// Solve Poisson's equation for a rectangular box with Dirichlet
/// boundary conditions on each face.
/// \param source is a pointer to a flattened 3-D array for the source function
/// \param potential is a pointer to a flattened 3-D array for the calculated potential
/// \param xsize is the number of elements in the x-direction
/// \param ysize is the number of elements in the y-direction
/// \param zsize is the number of elements in the z-direction
/// \param delta is the voxel spacing in all directions
/// \param numiters is the number of iterations to perform
/// \param numcores is the number of CPU cores to use.  If 0, an optimal number is chosen
/// \return 0 on success.


int matIndex(int i, int j, int k, int xsize, int ysize)
{
    return ((k * ysize) + j) * xsize + i;
}

int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       int xsize,  int ysize, int zsize,
                       double delta, int numiters, int numcores) 
{
    delta *= delta;
    int count, jj, ii, kk, index;
	omp_set_num_threads(numcores);
	omp_set_nested(1);
    double* pot_buff = (double *)calloc(xsize * ysize * zsize, sizeof(*potential));
    double* pot_temp = (double *)calloc(xsize * ysize * zsize, sizeof(*potential));

    for(count = 0;count<=numiters; count++){

			#pragma omp parallel for schedule(dynamic) firstprivate(jj) private(ii) lastprivate(kk) 
			for(kk = 1; kk<zsize-1; kk++){
				for(ii = 1; ii<ysize-1; ii++){
					for(jj = 1; jj<xsize-1; jj++){
						
						index = matIndex(jj,ii,kk,xsize,ysize);
						pot_buff[index] = (potential[index-1] + 			potential[index+1]
											+potential[index-xsize] + 		potential[index+xsize]
											+potential[index-xsize*ysize] + potential[index+xsize*ysize]
											-delta*source[index])		  * oneOsix;    
					}
				}
			}

		pot_temp = pot_buff;
		pot_buff = potential;
		potential = pot_temp;		
	}
    free(pot_temp);
	return 0;
}




