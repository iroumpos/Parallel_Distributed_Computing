#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <time.h>

#define N 500

int main(int argc,char*argv[]){
    /*int N;
    N = atoi(argv[1]);
    if(argc > 2 || argc == 0){
        printf("./ask5 [N]\n");
        return -1;
    }*/
    
    int rank,size;
    int A[N],B[N][N],C[N],B_temp[N][N];
    int sum[N];
    struct timespec t_start = {0,0}, t_stop = {0,0};

    //Start mpi program
    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int root = 0;
    int thread_workload = N/size;
    /*Initialise matrix-vector*/
    if (rank == root) {
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                B[i][j] = rand()%100;
            }
        }

        for(int i=0; i<N; i++){
            C[i] = rand()%100;
        }
    }

    /*Scatter matrix B row-wise*/
    MPI_Scatter(B, thread_workload*N, MPI_INT, B_temp, thread_workload*N, MPI_INT, 0, MPI_COMM_WORLD);

    /*Broadcast vector C */
    MPI_Bcast(C, N, MPI_INT, root, MPI_COMM_WORLD);

    /*Calculate inner product and save in sum*/
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    for(int i=0; i<(N/size); i++){
        for(int j=0; j<N; j++)
            sum[i] += C[j]*B_temp[i][j];
    }
    clock_gettime(CLOCK_MONOTONIC, &t_stop);

    /*Gather the results*/
    MPI_Gather(&sum, thread_workload, MPI_INT, A, thread_workload, MPI_INT, 0, MPI_COMM_WORLD);


/*printf("\n");
    if(rank == 0) {
        for(int i=0; i<N; i++){
            printf("A[%d]=%d\n", i,A[i]);
        }
    }*/

printf("Computation time is: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
    

    MPI_Finalize();
}
