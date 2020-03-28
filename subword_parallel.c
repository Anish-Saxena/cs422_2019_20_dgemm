#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<x86intrin.h>

void dgemm(int n, double* A, double* B, double* C){
	for(int i=0;i<n;i+=4){
		for(int j=0;j<n;++j){
			__m256d c0 = _mm256_load_pd(C+i+j*n);
			for(int k=0;k<n;k++)
				c0 = _mm256_add_pd(c0,
						_mm256_mul_pd(_mm256_load_pd(A+i+k*n),
							_mm256_broadcast_sd(B+k+j*n)));
			_mm256_store_pd(C+i+j*n,c0);
		}
	}
}

int main(){
	srand((unsigned int)time(NULL));
	float a = 32768.0;
	int n = 128;
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
