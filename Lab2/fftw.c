#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fftw3.h>

int main(int argc,char* argv[]){
    struct timespec tv1,tv2;
    int N = atoi(argv[1]);
    N = pow(2,N);
    
    fftw_complex *in,*out;
    fftw_plan p;
    
    in = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    for(int i=0; i < N; i++){
        in[i][0] = i+1;
        in[i][1] = 0;
    }

    out = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    p = fftw_plan_dft_1d(N, in, out, FFTW_FORWARD, FFTW_ESTIMATE);
    
    fftw_execute(p); /* repeat as needed */
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
    fftw_destroy_plan(p);

    printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));

    fftw_free(in); fftw_free(out);
    return 0;
}