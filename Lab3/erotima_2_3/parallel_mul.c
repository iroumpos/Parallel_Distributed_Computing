#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

int main(int argc,char**argv){
    if(argc != 3){
        printf("Give correct number of arguments!\n");
        printf("Correct form is: ./<name> <non zero elements> <size of vector>\n");
        return -1;
    }

     struct timespec  tv1, tv2;
    int NZ = atoi(argv[1]);
    NZ = pow(10,NZ);
    int size_of_vector = atoi(argv[2]);
    size_of_vector = pow(10,size_of_vector);

   
    int *sparse_A = malloc(sizeof(int) * NZ);  
    int *i_ptr = malloc(sizeof(int) * (size_of_vector + 1));
    int *j_index = malloc(sizeof(int) * size_of_vector);
    int *y = malloc(sizeof(int) * size_of_vector);
    int *x = malloc(sizeof(int) * size_of_vector);
    i_ptr[0] = 0;

    /*Initialize arrays*/
    for(int i=0; i < NZ; i++){
        sparse_A[i] = i + 1;
        j_index[i] = i%4;
    }

    /*Row offset*/
    for(int i=1; i < size_of_vector; i++){
        i_ptr[i] = i_ptr[i-1] +  NZ/size_of_vector; 
    }
    i_ptr[size_of_vector] = NZ;

    /*Vector initialization*/
    for(int i=0; i < size_of_vector; i++){
        x[i] = i + 1;
    }
    
    /*Start time*/
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    /*Calculate sparse matrix vector multiplication*/ 
    #pragma omp parallel for schedule(guided)
    for (int i=0; i < size_of_vector; i++){
        y[i] = 0;
        for (int j = i_ptr[i]; j < i_ptr[i+1]; j++){
            y[i] += sparse_A[j] * x[j_index[j]];
        }
    }
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
    /*Stop time*/

    printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));
    
    
    return 0;
}
