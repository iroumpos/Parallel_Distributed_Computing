#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <complex.h>
#include <string.h>
#include <time.h>
#include <omp.h>

#define pi 3.14159265358979323846

unsigned int bitReverse(unsigned int x, int size)
{
    int n = 0;
    for (int i = 0; i < log2(size); i++)
    {
        n <<= 1;
        n |= (x & 1);
        x >>= 1;
    }
    return n;
}

void fft(complex double* input, complex double* output, int size)
{
    int k,j,i;
    complex double expTable[size/2];

    // bit reversal of the given array
    for (i = 0; i < size; ++i) {
        int rev = bitReverse(i, size);
        output[i] = input[rev];
    }

    // Trigonometric Table
    for(k = 0; k < size / 2; k++){
        expTable[k] = cexp(-2*pi*k/size*I);
    }

    int n,halfsize,tablestep;
    double complex temp;

    // Cooley-Tukey decimation-in-time radix-2 FFt
    for(n = 2; n <= size; n *= 2){
        halfsize = n/2;
        tablestep = size / n;

        for(i = 0; i < size; i += n){
            for(j = i, k = 0; j < i + halfsize; j++, k += tablestep){
                temp = output[j + halfsize] * expTable[k];
                output[j + halfsize] = output[j] - temp;
                output[j] += temp; 
            }
        }

        if(n == size)   // Prevent overflow in size *= 2
            break;
    }
}
 


int main(int argc,char* argv[]){
    struct timespec  tv1, tv2;

    if(argc != 2){
        printf("Give correct number of arguments!!");
        return -1;
    }
    
    int n = atoi(argv[1]);
    if((ceil(log2(n)) != floor(log2(n)))){
        printf("Size must be a power of 2!!");
        return -1;
    }

    double complex* input = malloc(n*sizeof(double complex));
    if (input == NULL){
        printf("Error in malloc!");
        return -1;
    }
    double complex* output = malloc(n*sizeof(double complex));
    if (output == NULL){
        printf("Error in malloc!");
        return -1;
    }

    printf("Input array\n");
    for(int i=0; i<n; i++){
        input[i] = (i+1) + 0*I;
        printf("%lf + %lf*i\n",creal(input[i]),cimag(input[i]));
    }

    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    fft(input,output,n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);

    
    printf("\nOutput array\n");
    for(int i=0; i<n; i++){
        printf("%lf + %lf*i\n",creal(output[i]),cimag(output[i]));
    }
    
    printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));

    free(input);
    free(output);
    return 0;
}
