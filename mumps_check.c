#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "mpi.h"
#include "dmumps_c.h"
#define JOB_INIT -1
#define JOB_END -2
#define USE_COMM_WORLD -987654

double residual(int n, int nnz, double *rhs, MUMPS_INT *irn, MUMPS_INT *jcn, double *a, double *solution){
	//compute the residual Ax - b
	double r = .0;
	double norm_A = 0.;
	double norm_x = 0.;
	double *rhs_= (double *)calloc(n,sizeof(double));
	
	for (int i = 0; i< nnz; i ++){
		rhs_[irn[i]] += a[i]*solution[jcn[i]];
		norm_A += fabs(a[i]);
	}
	
		// printf("r = %e\n", r)	;
	for (int i = 0; i<n; i++){
		r = r + fabs(rhs[i] - rhs_[i]);
		norm_x +=fabs(solution[i]);
		// printf("r = %e\n", r)	;
	}
	free(rhs_);
	printf("residual = %e, ||A|| = %e, ||x|| = %e\n", r, norm_A, norm_x);
	return r / (norm_x * norm_A);
}

// double* mumps_solver(char* filename_matrix, char* filename_rhs){
	 // DMUMPS_STRUC_C id;
	  // MUMPS_INT n;
	  // MUMPS_INT8 nnz;
	  // get_size(&n, &nnz, filename_matrix); 
	  // printf("the matrix is %d x %d with %lld nonzero elements\n", n, n, nnz);
	  // MUMPS_INT* irn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
	  // MUMPS_INT* jcn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
	  // double* a = (double *) malloc(nnz * sizeof(double));
	  // double* rhs = (double *) malloc(nnz * sizeof(double));

	  // int myid, ierr;
	  // int error = 0;

	  // ierr = MPI_Init(&argc, &argv);
	  // ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);

	  // /* Define A and rhs */
	  // LoadMatrix(n, nnz, irn, jcn, a, filename_matrix);
	  
	  // double* rhs_ = (double *) malloc(nnz * sizeof(double));
	  // memcpy(rhs_, rhs, n);
	  
	  // if (argc >= 3) LoadRhs(n, rhs, filename_rhs);
	  // else {
		// for (int i = 0; i < n; i++){
		  // rhs[i] = 1;
		// }
	  // }

	  // /* Initialize a MUMPS instance. Use MPI_COMM_WORLD */
	  // id.comm_fortran=USE_COMM_WORLD; 
	  // id.par=1; id.sym=0;
	  // id.job=JOB_INIT;
	  // dmumps_c(&id);

	  // /* Define the problem on the host */
	  // if (myid == 0) {
		// id.n = n; id.nnz =nnz; id.irn=irn; id.jcn=jcn;
		// id.a = a; id.rhs = rhs;
	  // }

	// #define ICNTL(I) icntl[(I)-1] /* macro s.t. indices match documentation */

	  
	  // /* Call the MUMPS package (analyse, factorization and solve). */

	  // id.job=6;
	  // dmumps_c(&id);
	  // if (id.infog[0]<0) {
		// printf(" (PROC %d) ERROR RETURN: \tINFOG(1)= %d\n\t\t\t\tINFOG(2)= %d\n",
			// myid, id.infog[0], id.infog[1]);
		// error = 1;
	  // }

	  // /* Terminate instance. */
	  // id.job=JOB_END;
	  // dmumps_c(&id);

	  
	  
	  // ierr = MPI_Finalize();
	  // return ;
// }