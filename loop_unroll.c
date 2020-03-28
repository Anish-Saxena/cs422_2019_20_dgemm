#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<x86intrin.h>

#define UNROLL (64)

void dgemm(int n, double* A, double* B, double* C){
	for(int i=0;i<n;i+=UNROLL*4){
		for(int j=0;j<n;++j){
			__m256d c[UNROLL];
			for(int x=0;x<UNROLL;x++)
				c[x] = _mm256_load_pd(C+i+x*4+j*n);
			for(int k=0;k<n;k++){
				__m256d b = _mm256_broadcast_sd(B+k+j*n);
				for(int x=0;x<UNROLL;x++)
					c[x] = _mm256_add_pd(c[x],
							_mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i),b));
				for(int x=0;x<UNROLL;x++)
					_mm256_store_pd(C+i+x*4+j*n,c[x]);
			}
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
