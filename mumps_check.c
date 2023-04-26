#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include "mpi.h"
#include "dmumps_c.h"
#define JOB_INIT -1
#define JOB_END -2
#define USE_COMM_WORLD -987654

double residual(int n, int nnz, double *rhs, MUMPS_INT *irn, MUMPS_INT *jcn, double *a, double *solution){
	//compute the residual r = Ax - b
	double r = .0;
	// double* norm_A = (double *)malloc(n*sizeof(double));
	// double norm_inf_A = 0.0;
	// double norm_x = 0.;
	double *rhs_= (double *)malloc(n*sizeof(double));

	for (int i = 0; i<n; i++){
		rhs_[i] = 0.0;
		// norm_A[i] = 0.0;
	}
	
	for (int i = 0; i< nnz; i ++){
		rhs_[irn[i]-1] += a[i]*solution[jcn[i] - 1];
		// norm_A[irn[i] - 1] += fabs(a[i]);
	}


	for (int i = 0; i<n; i++){

		double ri = fabs(rhs[i] - rhs_[i]);
		if (ri > r) r = ri;

		// double xi = fabs(solution[i]);
		// if (xi > norm_x) norm_x = xi;

		// if (norm_inf_A < norm_A[i]) norm_inf_A = norm_A[i];
	}

	free(rhs_);
	return r;
}