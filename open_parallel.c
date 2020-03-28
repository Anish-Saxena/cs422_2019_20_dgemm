#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<x86intrin.h>

#define UNROLL (4)
#define BLOCKSIZE 512

void do_block(int n, int si, int sj, int sk, double* A, double *B, double *C){
	for(int i=si;i<si+BLOCKSIZE;i+=UNROLL*4)
		for(int j=sj;j<sj+BLOCKSIZE;j++){
			__m256d c[UNROLL];
			for(int x=0;x<UNROLL;x++)
				c[x] = _mm256_load_pd(C+i+x*4+j*n);
			for(int k=sk;k<sk+BLOCKSIZE;k++){
				__m256d b = _mm256_broadcast_sd(B+k+j*n);
				for(int x=0;x<UNROLL;x++)
					c[x] = _mm256_add_pd(c[x],
							_mm256_mul_pd(_mm256_load_pd(A+n*k+x*4+i),b));
			}
			for(int x=0;x<UNROLL;x++)
				_mm256_store_pd(C+i+x*4+j*n,c[x]);
		}
}


void dgemm(int n, double* A, double* B, double* C){
#pragma omp parallel for	
	for(int sj=0;sj<n;sj+=BLOCKSIZE)
		for(int si=0;si<n;si+=BLOCKSIZE)
			for(int sk=0;sk<n;sk+=BLOCKSIZE)
				do_block(n,si,sj,sk,A,B,C);
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
