#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <math.h>
#include <time.h>

void jacobi(int n, int* IA, int* JA, double* A, double* b, double* x, int max_iter) {
    int i, j, k;
    double sum, x_new, residual, difference;
    double* x_old = (double*) malloc(n * sizeof(double));
    double* Ax = (double*) malloc(n * sizeof(double));
    double* diff_mat = (double * ) malloc(n * sizeof(double));

	#pragma omp for schedule(dynamic) private(i)
    for (i = 0; i < n; i++) {
        x_old[i] = 0.0;
    }

    #pragma omp parallel private(i, j, k, sum, x_new)
    {
        for (i = 0; i < max_iter; i++) {
            #pragma omp for schedule(dynamic)
            for (j = 0; j < n; j++) {
                sum = b[j];
                for (k = IA[j]; k < IA[j+1]; k++) {
                    if (JA[k] != j) {
                        sum -= A[k] * x_old[JA[k]];
                    }
                }
                if(j == 0) {
					x_new = sum / A[IA[j]];
				}
				else {
					x_new = sum / A[IA[j]+1];
				}
                x[j] = x_new;
            }
            #pragma omp barrier
            {
                // Compute residual
				#pragma omp for schedule(dynamic)
                for (j = 0; j < n; j++) {
                    Ax[j] = b[j];
                    for (k = IA[j]; k < IA[j+1]; k++) {
                        Ax[j] -= A[k] * x[JA[k]];
                    }
                }
                residual = 0.0;
                #pragma omp for schedule(dynamic) reduction(+:residual)
                for (j = 0; j < n; j++) {
                    residual += Ax[j] * Ax[j];
                }
                residual = sqrt(residual);

				// Compute difference
                #pragma omp for schedule(dynamic)
                for(j = 0; j < n; j++){
                    diff_mat[j] = x_old[j] - x[j];
                }

                difference = 0.0;
                #pragma omp for schedule(dynamic) reduction(+:difference)
                for (j = 0; j < n; j++) {
                    difference += diff_mat[j] * diff_mat[j];
                }
                difference = sqrt(difference);
                
                printf("Iter = %d, residual = %lf, difference = %lf\n", i, residual, difference);
                
                #pragma omp for schedule(dynamic)
                for (j = 0; j < n; j++) {
                    x_old[j] = x[j];
                }
            }
        }
    }
    free(x_old);
    free(Ax);
    free(diff_mat);
}


int main() {
    int i;
    int n = 1000000;
    int max_iter = 1000;
    double* A_values = (double*) malloc((3*n-2)* sizeof(double));
    double* b = (double*) malloc(n * sizeof(double));
    double* x = (double*) malloc(n * sizeof(double));
    int* i_ptr = (int*) malloc((n+1) * sizeof(int));
    int* j_index = (int*) malloc((3*n-2)* sizeof(int));
	struct timespec tv1,tv2;

	/*Init A Values*/
	A_values[0] = 2;
	A_values[1] = -1;
	A_values[3*n - 4] = -1;
	A_values[3*n - 3] = 2;

	/*Init i_ptr*/
	i_ptr[0] = 0;
	i_ptr[1] = 2;
	i_ptr[n] = 3*n - 2;
	//i_ptr[n] = 3*n - 1;

	/*Init j_index*/
	j_index[0] = 0;
	j_index[1] = 1;
	j_index[3*n - 4] = n-2;
	j_index[3*n - 3] = n-1;


    // Initialize the matrix and right-hand side
    # pragma omp parallel private ( i )
    {
    /*Init A values*/
    #pragma omp for
    for ( i = 2; i < 3*n - 4; i = i + 3){
        A_values[i] =  -1;
        A_values[i + 1] = 2;
        A_values[i + 2] = -1;
    }

    #pragma omp for
    for( i = 2; i < n; i++){
        i_ptr[i] = 3*i - 1;
    }

    #pragma omp for
    for( i = 2; i < 3*n - 4; i = i+3){
        j_index[i] = i/3;
        j_index[i + 1] = j_index[i] + 1;
        j_index[i + 2] = j_index[i] + 2;
    }

    /*
    Set up the right hand side.
    */
    # pragma omp for
        for ( i = 0; i < n; i++ )
        {
        b[i] = 0.0;
        }

        b[n-1] = ( double ) ( n + 1 );
    /*
    Initialize the solution estimate to 0.
    Exact solution is (1,2,3,...,N).
    */
    # pragma omp for
        for ( i = 0; i < n; i++ )
        {
        x[i] = 0.0;
        }

    }
  
    /*printf("A_vals: ");
    for( i =0; i < 3*n-2; i++){
    printf("%d ", (int)A_values[i]);
    }
    printf("\ni_ptr: ");
    for( i =0; i < n+1; i++){
    printf("%d ", i_ptr[i]);
    }
    printf("\nj_index: ");
    for( i =0; i < 3*n-2; i++){
    printf("%d ", j_index[i]);
    }
    printf("\nb: ");
    for( i =0; i < n; i++){
    printf("%f ", b[i]);
    }
    printf("\n");*/
  
    // Call the Jacobi method
    clock_gettime(CLOCK_MONOTONIC_RAW, &tv1);
    jacobi(n, i_ptr, j_index, A_values, b, x, max_iter);
     clock_gettime(CLOCK_MONOTONIC_RAW, &tv2);
    
    // Print the solution
    /*for (i = 0; i < n; i++) {
        printf("x[%d] = %f\n", i, x[i]);
    }*/

    printf ("Total time = %10g seconds\n",
			(double) (tv2.tv_nsec - tv1.tv_nsec) / 1000000000.0 +
			(double) (tv2.tv_sec - tv1.tv_sec));
            
    free(A_values);
    free(b);
    free(x);
    free(i_ptr);
    free(j_index);
    return 0;
}
