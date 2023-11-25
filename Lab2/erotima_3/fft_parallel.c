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
    complex double *expTable = malloc(size/2*sizeof(double complex));
    if(expTable == NULL)
        return;

    // bit reversal of the given array
    #pragma omp parallel for shared(output) private(i)
    for (i = 0; i < size; ++i) {
        int rev = bitReverse(i, size);
        output[i] = input[rev];
    }

    #pragma omp parallel for shared(expTable,size) private(k)
    for(k = 0; k < size / 2; k++){
        expTable[k] = cexp(-2*pi*k/size*I);
    }

    int n,halfsize,tablestep;
    double complex temp;

    #pragma omp parallel private(n,halfsize,tablestep,i,j,k,temp) shared(output)
    {
    for(n = 2; n <= size; n *= 2){
        halfsize = n/2;
        tablestep = size / n;
    
    #pragma omp for
        for(i = 0; i < size; i += n){
            for(j = i, k = 0; j < i + halfsize; j++, k += tablestep){
                temp = output[j + halfsize] * expTable[k];
                output[j + halfsize] = output[j] - temp;
                output[j] += temp; 
            }
        }

        if(n == size)
            break;
    }
    }
    free(expTable);
}
 


int main(int argc,char* argv[]){
    struct timespec  tv1, tv2;

    if(argc != 2){
        printf("Give correct number of arguments!!");
        return -1;
    }
    
    int n = atoi(argv[1]);
    n = pow(2,n);

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

    /*printf("Input array\n");
    for(int i=0; i<n; i++){
        input[i] = (i+1) + 0*I;
        printf("%lf + %lf*i\n",creal(input[i]),cimag(input[i]));
    }*/

    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    fft(input,output,n);
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);

    
    /*printf("\nOutput array\n");
    for(int i=0; i<n; i++){
        printf("%lf + %lf*i\n",creal(output[i]),cimag(output[i]));
    }*/
    printf("N = %.2lf ",log2(n));
    printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));

    free(input);
    free(output);
    return 0;
}
