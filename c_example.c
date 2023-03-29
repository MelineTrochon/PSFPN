/*
 *
 *  This file is part of MUMPS 5.5.1, released
 *  on Tue Jul 12 13:17:24 UTC 2022
 *
 */

/*phase: 
	job = 1 analisys : prepare for the factorization (matrix format, ICNTL 5)
	job = 2 factorization :
	job = 3 solve
	
file??
BLR??

ICNTL 7, 28, 29 way of computing the permutation matrix (parallel or sequential, or ..)
7 -> bon paramètre



ICNTL 11 error analysis

ICNTL 10 iterative refinement, number of step, error.., better accuracy

forward elimination during the factorization: out of core context? (ICNTL 32)	 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include "dmumps_c.h"
#define JOB_INIT -1
#define JOB_END -2
#define USE_COMM_WORLD -987654


void get_size(MUMPS_INT *n, MUMPS_INT8 *nnz, char *filename){
	FILE *f = fopen(filename, "r");
	int e, m;
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit( 0 );
    	}
    	
    	while (fgets(str, 256, f) != NULL) {
        	if (str[0] != '%'){
        		e = sscanf(str, "%d %d %ld \n", n, &m, nnz);
        		break;
        	}
    	}
    	
    	
    	return ;
  }


void LoadMatrix(MUMPS_INT n, MUMPS_INT8 nnz, MUMPS_INT *irn, MUMPS_INT *jcn, double *a, char *filename){
	int e, m;
	FILE *f = fopen(filename, "r");
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit( 0 );
    	}
    	MUMPS_INT n_; MUMPS_INT8 nnz_;
    	
	int r, c;
	double v;
	
	
	
	while (fgets(str, 256, f) != NULL) {
		
        	if (str[0] != '%'){
        		e = sscanf(str, "%d %d %ld \n", &n_, &m, &nnz_);
        		break;
        	}
    	}
	
	
	if (n_!=n || nnz_ != nnz){
		printf(" Cannot load the matrix, wrong size\n");
		exit(0);
	}	
	
	
	for (int i = 0; i< nnz; i++){
		e = fscanf(f, "%d %d %lf \n", &r, &c, &v);
		irn[i] = r;
		jcn[i] = c;
		a[i] = v;
		
	}
	
	fclose(f);
	
	return ;
}



int main(int argc, char ** argv)
{

  char* filename = "Poisson_2D/Poisson_2D.m";
  DMUMPS_STRUC_C id;
  MUMPS_INT n;
  MUMPS_INT8 nnz;
  get_size(&n, &nnz, filename); 
  printf("the matrix is %d x %d with %d nonzero elements\n", n, n, nnz);
  MUMPS_INT* irn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
  // printf("apres irn\n");
  MUMPS_INT* jcn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
  double* a = (double *) malloc(nnz * sizeof(double));
  
  
  
  double* rhs = (double *) malloc(nnz * sizeof(double));


  int myid, ierr;

  int error = 0;

  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);
  /* Define A and rhs */
  LoadMatrix(n, nnz, irn, jcn, a, filename);
  

  for (int i = 0; i < n; i++){
  	rhs[i]=1.0;
  }
  
    // for (int i = 0; i < nnz; i++){
		// printf("i = %d, IRN = %d, JCN = %d, A = %f\n", i, irn[i], jcn[i], a[i]);
	// }

  /* Initialize a MUMPS instance. Use MPI_COMM_WORLD */
  id.comm_fortran=USE_COMM_WORLD; 
  id.par=1; id.sym=0;
  id.job=JOB_INIT;
  dmumps_c(&id);

  /* Define the problem on the host */
  if (myid == 0) {
    id.n = n; id.nnz =nnz; id.irn=irn; id.jcn=jcn;
    id.a = a; id.rhs = rhs;
  }
#define ICNTL(I) icntl[(I)-1] /* macro s.t. indices match documentation */

  id.ICNTL(1)=-1;  //output for error message
  id.ICNTL(2)=5; //output stream for diagnostic printing and statistics local to each MPI process?
  // id.ICNTL(3)=-1; id.ICNTL(4)=0; id.ICNTL(11)=1;
  
  /* Call the MUMPS package (analyse, factorization and solve). */
  // id.job=1;
  // dmumps_c(&id);
  // id.job=2;
  // dmumps_c(&id);
  id.job=6;
  dmumps_c(&id);
  if (id.infog[0]<0) {
    printf(" (PROC %d) ERROR RETURN: \tINFOG(1)= %d\n\t\t\t\tINFOG(2)= %d\n",
        myid, id.infog[0], id.infog[1]);
    error = 1;
  }
	


  /* Terminate instance. */
  id.job=JOB_END;
  dmumps_c(&id);
  if (myid == 0) {
    if (!error) {
	  printf("Solution is :(");
	  for (int i = 0; i< n; i++){
		printf("%8.2f  \t", rhs[i]);
	  }
	  printf(")\n");
    } else {
      printf("An error has occured, please check error code returned by MUMPS.\n");
    }
  }
  

    printf(" (PROC %d) ERROR  ANALYSIS RETURN: \tINFOG(9)= %d\n\t\t\t\tINFOG(7)= %d\n\t\t\t\tINFOG(8) = %d\n",
        myid, id.infog[8], id.infog[6], id.infog[7]);
  
  
  ierr = MPI_Finalize();
  return 0;
}
	
	
