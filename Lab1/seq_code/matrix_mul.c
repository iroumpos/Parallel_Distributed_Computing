#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



void init_matrixes(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            matrix1[i][j] = rand()%100;
            matrix2[i][j] = rand()%100;
        }
    }
}

void mul_s1(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            result[i][j] = 0;
            for(int k = 0; k < 512; k++){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }

    return;
}

void mul_s2(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            result[i][j] = 0;
            for(int k = 0; k < 512; k = k + 2){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
                result[i][j] += matrix1[i][k+1]*matrix2[k+1][j];
            }
        }
    }

    return;
}

void mul_s4(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            result[i][j] = 0;
            for(int k = 0; k < 512; k = k + 4){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
                result[i][j] += matrix1[i][k+1]*matrix2[k+1][j];
                result[i][j] += matrix1[i][k+2]*matrix2[k+2][j];
                result[i][j] += matrix1[i][k+3]*matrix2[k+3][j];
            }
        }
    }

    return;
}

void mul_s8(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            result[i][j] = 0;
            for(int k = 0; k < 512; k = k + 8){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
                result[i][j] += matrix1[i][k+1]*matrix2[k+1][j];
                result[i][j] += matrix1[i][k+2]*matrix2[k+2][j];
                result[i][j] += matrix1[i][k+3]*matrix2[k+3][j];
                result[i][j] += matrix1[i][k+4]*matrix2[k+4][j];
                result[i][j] += matrix1[i][k+5]*matrix2[k+5][j];
                result[i][j] += matrix1[i][k+6]*matrix2[k+6][j];
                result[i][j] += matrix1[i][k+7]*matrix2[k+7][j];
            }
        }
    }

    return;
}

void mul_s16(int** matrix1,int** matrix2,double** result){
    
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            result[i][j] = 0;
            for(int k = 0; k < 512; k = k + 16){
                result[i][j] += matrix1[i][k] * matrix2[k][j];
                result[i][j] += matrix1[i][k+1]*matrix2[k+1][j];
                result[i][j] += matrix1[i][k+2]*matrix2[k+2][j];
                result[i][j] += matrix1[i][k+3]*matrix2[k+3][j];
                result[i][j] += matrix1[i][k+4]*matrix2[k+4][j];
                result[i][j] += matrix1[i][k+5]*matrix2[k+5][j];
                result[i][j] += matrix1[i][k+6]*matrix2[k+6][j];
                result[i][j] += matrix1[i][k+7]*matrix2[k+7][j];
                result[i][j] += matrix1[i][k+8]*matrix2[k+8][j];
                result[i][j] += matrix1[i][k+9]*matrix2[k+9][j];
                result[i][j] += matrix1[i][k+10]*matrix2[k+10][j];
                result[i][j] += matrix1[i][k+11]*matrix2[k+11][j];
                result[i][j] += matrix1[i][k+12]*matrix2[k+12][j];
                result[i][j] += matrix1[i][k+13]*matrix2[k+13][j];
                result[i][j] += matrix1[i][k+14]*matrix2[k+14][j];
                result[i][j] += matrix1[i][k+15]*matrix2[k+15][j];
            }
        }
    }

    return;
}

/*int cpy_matrix(double** temp,double** result){
    for(int i=0; i<512; i++){
        for(int j=0; j<512; j++){
            temp[i][j] = result[i][j];
        }
    }
    return 0;
}

int print_matrix(double** temp){
    for(int i=0; i<10; i++){
        for(int j=0; j<10; j++){
            printf("%lf ",temp[i][j]);
        }
        printf("\n");
    }
    return 0;
}*/

int main(int argc,char* argv[]){
    int **matrix1, **matrix2;
    double **result;
   // double** temp;
   struct timespec t_start = {0,0}, t_stop = {0,0};

    matrix1 = (int**)malloc(512*sizeof(int*));
    for(int i=0; i<512; i++){
        matrix1[i] = (int*)malloc(512*sizeof(int));
    }
    matrix2 = (int**)malloc(512*sizeof(int*));
    for(int i=0; i<512; i++){
        matrix2[i] = (int*)malloc(512*sizeof(int));
    }
    result  = (double**)malloc(512*sizeof(double*));
    for(int i=0; i<512; i++){
        result[i] = (double*)malloc(512*sizeof(double));
    }

    /*temp  = (double**)malloc(512*sizeof(double*));
    for(int i=0; i<512; i++){
        temp[i] = (double*)malloc(512*sizeof(double));
    }*/

    if (matrix1 == NULL || matrix2 == NULL || result == NULL)
        return -1;

    init_matrixes(matrix1,matrix2,result);
    
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    mul_s1(matrix1,matrix2,result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    printf("Total time for k = 1: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
    

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    mul_s2(matrix1,matrix2,result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    printf("Total time for k = 2: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
    
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    mul_s4(matrix1,matrix2,result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    printf("Total time for k = 4: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
   
   
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    mul_s8(matrix1,matrix2,result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    printf("Total time for k = 8: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
   
   
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    mul_s16(matrix1,matrix2,result);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    printf("Total time for k = 16: %.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
   
    return 0;
}