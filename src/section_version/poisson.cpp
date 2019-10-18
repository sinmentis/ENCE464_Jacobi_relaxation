#include "poisson.hpp"
#include <omp.h>
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


int matIndex(unsigned int i, unsigned int j, unsigned int k,
	     unsigned int xsize, unsigned int ysize)
{
    return ((k * ysize) + j) * xsize + i;
}

int poisson_dirichlet (double * __restrict__ source, double *__restrict__ potential,
                       unsigned int xsize,  unsigned int ysize, unsigned int zsize,
                       double delta, unsigned int numiters, unsigned int numcores) {
    //delta *= delta;
    int index;
    unsigned int halfxsize = xsize/2;
    unsigned int halfysize = ysize/2;
    unsigned int halfzsize = zsize/2;
    omp_set_num_threads(numcores);
    int mid = matIndex(halfxsize,halfysize,halfzsize,xsize,ysize);
    double* potentialBuffer = (double *)calloc(xsize * ysize * zsize, sizeof(*potential));
    double* pot_temp;
    for(unsigned int count = 0;count<=numiters; count++){
    #pragma omp parallel sections
    {
	    #pragma omp section
	    {
		for(int aa = 1; aa<halfzsize; aa++){
		    for(int bb = 1; bb<halfysize; bb++){
			for(int cc = 1; cc<xsize-1; cc++){
			    index = matIndex(cc,bb,aa,xsize,ysize);
			    potentialBuffer[index] = getJ(source,potential,index,xsize,ysize, zsize, delta);
			}
		    }
		}
	    }
	    #pragma omp section
	    {
		for(int dd = halfzsize; dd<zsize-1; dd++){
		    for(int ee =1; ee < halfysize; ee++){
			for(int ff = 1; ff<xsize-1; ff++){
			    index = matIndex(ff,ee,dd,xsize,ysize);
			    potentialBuffer[index] = getJ(source,potential,index,xsize,ysize, zsize, delta);
			}
		    }
		}
	    }
	   
	    #pragma omp section
	    {
		for(int kk = 1; kk<halfzsize; kk++){
		    for(int jj = halfysize; jj<ysize-1; jj++){
			for(int ll = 1; ll<xsize-1; ll++){
			    index = matIndex(ll,jj,kk,xsize,ysize);
			    potentialBuffer[index] = getJ(source,potential,index,xsize,ysize, zsize, delta);
			}
		    }
		}
	    }

	     #pragma omp section
	    {
		for(int gg = halfzsize; gg<zsize-1; gg++){
		    for(int hh = halfysize;hh<ysize-1;hh++){
			for(int ii = 1; ii<xsize-1; ii++){
			    index = matIndex(ii,hh,gg,xsize,ysize);
			    potentialBuffer[index] = getJ(source,potential,index,xsize,ysize, zsize, delta);
			}
		    }
		}
	    }
	}
		pot_temp = potentialBuffer;
		potentialBuffer = potential;
		potential = pot_temp;
    }		    
    return 0;
}

static inline double getJ(double * __restrict__ source, double *__restrict__ potential,
		   unsigned int index,unsigned int xsize,  unsigned int ysize,
		   unsigned int zsize, double delta) {
    return (potential[index-1]+potential[index+1]+potential[index-xsize]
	    +potential[index+xsize]+potential[index-xsize*ysize]
	    +potential[index+xsize*ysize]-delta*source[index])*oneOsix;
}
