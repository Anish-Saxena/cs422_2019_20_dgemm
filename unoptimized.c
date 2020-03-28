#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void dgemm(int n, double* A, double* B, double* C){
	for(int i=0;i<n;++i){
		for(int j=0;j<n;++j){
			double cij = C[i+j*n];
			for(int k=0;k<n;k++)
				cij += A[i+k*n]*B[k+j*n];
			C[i+j*n] = cij;
		}
	}
}

int main(){
	srand((unsigned int)time(NULL));
	float a = 32768.0;
	int n = 32;
	double *A = (double *)malloc(sizeof(double)*n*n);
        double *B = (double *)malloc(sizeof(double)*n*n);
        double *C = (double *)malloc(sizeof(double)*n*n);
	for(int i=0;i<n*n;i++){
		A[i] = ((float)rand()/(float)(RAND_MAX))*a;
		B[i] = ((float)rand()/(float)(RAND_MAX))*a;
		C[i] = ((float)rand()/(float)(RAND_MAX))*a;
	}
	dgemm(n,A,B,C);
	return 0;
}
