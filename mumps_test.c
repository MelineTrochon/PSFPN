#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mpi.h"
#include "dmumps_c.h"
#include <time.h>
#define JOB_INIT -1
#define JOB_END -2
#define USE_COMM_WORLD -987654


void get_size(MUMPS_INT *, MUMPS_INT8 *, char *);

void LoadMatrix(MUMPS_INT, MUMPS_INT8, MUMPS_INT *, MUMPS_INT *, double *, char *);

void LoadRhs(MUMPS_INT, double *, char *);

double residual(int , MUMPS_INT8, double*, MUMPS_INT *, MUMPS_INT *, double*, double*);


int main(int argc, char ** argv){

   if (argc < 5){
	   printf("error: nombre d'arguments\n");
     exit(1);
   }
   
  
  char* filename_matrix = argv[1];
  char* filename_rhs = argv[2];
  DMUMPS_STRUC_C id;
  MUMPS_INT n;
  MUMPS_INT8 nnz;
  get_size(&n, &nnz, filename_matrix); 
  printf("the matrix is %d x %d with %lld nonzero elements\n", n, n, nnz);
  MUMPS_INT* irn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
  MUMPS_INT* jcn = (MUMPS_INT *) malloc(nnz * sizeof(MUMPS_INT));
  double* a = (double *) malloc(nnz * sizeof(double));
  double* rhs = (double *) malloc(n * sizeof(double));

  int myid, ierr;
  int error = 0;

  ierr = MPI_Init(&argc, &argv);
  ierr = MPI_Comm_rank(MPI_COMM_WORLD, &myid);

  int sym = atoi(argv[4]);
  /* Define A and rhs */
  if (sym != 0) LoadMatrix_sym(n, nnz, irn, jcn, a, filename_matrix);
  else LoadMatrix(n, nnz, irn, jcn, a, filename_matrix);

  LoadRhs(n, rhs, filename_rhs);
  // else {
    // for (int i = 0; i < n; i++){
    //   rhs[i] = 1;
    // }
  // }
  
    // for (int i = 0; i < nnz; i++){
		// printf("i = %d, IRN = %d, JCN = %d, A = %f\n", i, irn[i], jcn[i], a[i]);
	// }

  double* _rhs = (double *) malloc(n * sizeof(double));
  memcpy(_rhs, rhs, n*sizeof(double));
	
	 // for (int i = 0; i < n; i++){
		// printf("i = %d,  rhs = %f, _rhs = %f\n", i, rhs[i], _rhs[i]);
	// }

  /* Initialize a MUMPS instance. Use MPI_COMM_WORLD */
  id.comm_fortran=USE_COMM_WORLD; 
  id.par=1; id.sym=sym;
  id.job=JOB_INIT;
  dmumps_c(&id);

  /* Define the problem on the host */
  if (myid == 0) {
    id.n = n; id.nnz =nnz; id.irn=irn; id.jcn=jcn;
    id.a = a; id.rhs = rhs;
  }

  #define ICNTL(I) icntl[(I)-1] /* macro s.t. indices match documentation */
  id.ICNTL(11) = 2;
  id.ICNTL(7) = atoi(argv[5]);
  // id.ICNTL(8) = 8;

  
  /* Call the MUMPS package (analyse, factorization and solve). */
  id.job=1;
  time_t deb = time(NULL);
  dmumps_c(&id);
  time_t fin = time(NULL);
  unsigned long t_analysis = difftime(fin, deb);

  id.job=2;
  deb = time(NULL);
  dmumps_c(&id);
  fin = time(NULL);
  unsigned long t_factorisation = difftime(fin, deb);

  id.job=3;
  deb = time(NULL);
  dmumps_c(&id);
  fin = time(NULL);
  unsigned long t_check = difftime(fin, deb);

  if (id.infog[0]<0) {
    printf(" (PROC %d) ERROR RETURN: \tINFOG(1)= %d\n\t\t\t\tINFOG(2)= %d\n",
        myid, id.infog[0], id.infog[1]);
    error = 1;
  }

  FILE * f = fopen(argv[3], "a");
  fprintf(f, "%d : %ld\t%ld\t%ld\n", id.ICNTL(7), t_analysis, t_factorisation, t_check);
  fclose(f);
  // printf("infog[7] = %d, infog[8] = %d\n",id.infog[6], id.infog[32]);

  /* Terminate instance. */
  id.job=JOB_END;
  dmumps_c(&id);
  // if (myid == 0) {
    // if (!error) {
	  // printf("Solution is :(");
	  // for (int i = 0; i< n; i++){
		// printf("%8.2f  \t", rhs[i]);
	  // }
	  // printf(")\n");
    // } else {
      // printf("An error has occured, please check error code returned by MUMPS.\n");
    // }
	
	// double r = residual(n, nnz, _rhs, irn, jcn, a, rhs);
	// printf("the residual is %e \n", r);
	
  free(irn);
  free(jcn);
  free(a);
  free(rhs);
  free(_rhs);

	ierr = MPI_Finalize();
  return 0;
}