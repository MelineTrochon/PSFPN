#include <stdio.h>
#include <stdlib.h>
#include "dmumps_c.h"
#include <string.h>



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
        		e = sscanf(str, "%d %d %lld \n", n, &m, nnz);
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
			e = sscanf(str, "%d %d %lld \n", &n_, &m, &nnz_);
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

void LoadRhs(MUMPS_INT n, double *rhs, char *filename){
	int e;
	FILE *f = fopen(filename, "r");
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit(1);
    	}

	double v;
		
	while (fgets(str, 256, f) != NULL) {
		
		if (str[0] != '%'){
			e = sscanf(str, "%lf \n", &v);
			rhs[0] = v;
			break;
		}
    }
	
	for (int i = 1; i< n; i++){
		e = fscanf(f, "%lf \n", &v);
		rhs[i] = v;
		
	}
	
	fclose(f);
	
	return ;
}

void LoadMatrix_sym(MUMPS_INT n, MUMPS_INT8 nnz, MUMPS_INT *irn, MUMPS_INT *jcn, double *a, char *filename){
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
			e = sscanf(str, "%d %d %lld \n", &n_, &m, &nnz_);
			break;
		}
	}
	
	
	if (n_!=n || nnz_ != nnz){
		printf(" Cannot load the matrix, wrong size\n");
		exit(0);
	}	
	
	
	for (int i = 0; i< nnz; i++){
		e = fscanf(f, "%d %d %lf \n", &r, &c, &v);
		if ( r <= c) {
			irn[i] = r;
			jcn[i] = c;
			a[i] = v;
		}
	}
	
	fclose(f);
	
	return ;
}

void LoadMatrix_float(MUMPS_INT n, MUMPS_INT8 nnz, MUMPS_INT *irn, MUMPS_INT *jcn, float *a, char *filename){
	int e, m;
	FILE *f = fopen(filename, "r");
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit( 0 );
    	}
    	MUMPS_INT n_; MUMPS_INT8 nnz_;
    	
	int r, c;
	float v;
	
	
	
	while (fgets(str, 256, f) != NULL) {
		
		if (str[0] != '%'){
			e = sscanf(str, "%d %d %lld \n", &n_, &m, &nnz_);
			break;
		}
	}
	
	
	if (n_!=n || nnz_ != nnz){
		printf(" Cannot load the matrix, wrong size\n");
		exit(0);
	}	
	
	
	for (int i = 0; i< nnz; i++){
		e = fscanf(f, "%d %d %f \n", &r, &c, &v);
		irn[i] = r;
		jcn[i] = c;
		a[i] = v;
		
	}
	
	fclose(f);
	
	return ;
}

void LoadRhs_float(MUMPS_INT n, float *rhs, char *filename){
	int e;
	FILE *f = fopen(filename, "r");
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit(1);
    	}

	float v;
		
	while (fgets(str, 256, f) != NULL) {
		
		if (str[0] != '%'){
			e = sscanf(str, "%f \n", &v);
			rhs[0] = v;
			break;
		}
    }
	
	for (int i = 1; i< n; i++){
		e = fscanf(f, "%f \n", &v);
		rhs[i] = v;
		
	}
	
	fclose(f);
	
	return ;
}

void LoadMatrix_sym_float(MUMPS_INT n, MUMPS_INT8 nnz, MUMPS_INT *irn, MUMPS_INT *jcn, float *a, char *filename){
	int e, m;
	FILE *f = fopen(filename, "r");
	char str[256];
	
	if ( f == NULL ) {
        	printf( "Cannot open file %s\n", filename );
        	exit( 0 );
    	}
    	MUMPS_INT n_; MUMPS_INT8 nnz_;
    	
	int r, c;
	float v;
	
	
	
	while (fgets(str, 256, f) != NULL) {
		
		if (str[0] != '%'){
			e = sscanf(str, "%d %d %lld \n", &n_, &m, &nnz_);
			break;
		}
	}
	
	
	if (n_!=n || nnz_ != nnz){
		printf(" Cannot load the matrix, wrong size\n");
		exit(0);
	}	
	
	
	for (int i = 0; i< nnz; i++){
		e = fscanf(f, "%d %d %f \n", &r, &c, &v);
		if ( r <= c) {
			irn[i] = r;
			jcn[i] = c;
			a[i] = v;
		}
	}
	
	fclose(f);
	
	return ;
}