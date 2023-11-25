#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void init_vectors(int* vector1,int* vector2){

    for(int i=0; i<220; i++){
        vector1[i] = rand()%100;
        vector2[i] = rand()%100;
    }    
}

double inner_p_1(int* vector1,int* vector2){
    double sum = 0;
    
    for(int i=0; i<220; i++){
        sum += vector1[i]*vector2[i];
    }

    return sum;
}


double inner_p_2(int* vector1,int* vector2){
    double sum = 0;

    for(int i=0; i<220; i = i + 2){
        sum += vector1[i]*vector2[i];
        sum += vector1[i+1]*vector2[i+1];
    }

    return sum;
}

double inner_p_4(int* vector1,int* vector2){
    double sum = 0;

    for(int i=0; i<220; i = i + 4){
        sum += vector1[i]*vector2[i];
        sum += vector1[i+1]*vector2[i+1];
        sum += vector1[i+2]*vector2[i+2];
        sum += vector1[i+3]*vector2[i+3];
    }

    return sum;
}

double inner_p_8(int* vector1,int* vector2){
    double sum = 0;

    for(int i=0; i<220; i = i + 8){
        sum += vector1[i]*vector2[i];
        sum += vector1[i+1]*vector2[i+1];
        sum += vector1[i+2]*vector2[i+2];
        sum += vector1[i+3]*vector2[i+3];
        if(i < 216){
            sum += vector1[i+4]*vector2[i+4];
            sum += vector1[i+5]*vector2[i+5];
            sum += vector1[i+6]*vector2[i+6];
            sum += vector1[i+7]*vector2[i+7];
        }
    }

    return sum;
}


double inner_p_16(int* vector1,int* vector2){
    double sum = 0;

    for(int i=0; i<220; i = i + 16){
        sum += vector1[i]*vector2[i];
        sum += vector1[i+1]*vector2[i+1];
        sum += vector1[i+2]*vector2[i+2];
        sum += vector1[i+3]*vector2[i+3];
        sum += vector1[i+4]*vector2[i+4];
        sum += vector1[i+5]*vector2[i+5];
        sum += vector1[i+6]*vector2[i+6];
        sum += vector1[i+7]*vector2[i+7];
        sum += vector1[i+8]*vector2[i+8];
        sum += vector1[i+9]*vector2[i+9];
        sum += vector1[i+10]*vector2[i+10];
        sum += vector1[i+11]*vector2[i+11];
        if(i < 208){
            sum += vector1[i+12]*vector2[i+12];
            sum += vector1[i+13]*vector2[i+13];
            sum += vector1[i+14]*vector2[i+14];
            sum += vector1[i+15]*vector2[i+15];
        }
    }

    return sum;
}

int main(int argc,char* argv[]){
    
    int *vector1 = NULL,*vector2 = NULL;
    double sum;
    struct timespec t_start = {0,0}, t_stop = {0,0};
   
    vector1 = (int*)malloc(220*sizeof(int));
    vector2 = (int*)malloc(220*sizeof(int));

    if(vector1 == NULL || vector2 == NULL )
        return -1;
    init_vectors(vector1,vector2);

    
    
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sum = inner_p_1(vector1,vector2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    /*printf("Total time taken for step = 1: %.9f milliseconds and result = %lf\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000,sum);*/
    printf("%.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
    
   
    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sum = inner_p_2(vector1,vector2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    /*printf("Total time taken for step = 2: %.9f milliseconds and result = %lf\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000,sum);*/
     printf("%.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sum = inner_p_4(vector1,vector2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    /*printf("Total time taken for step = 4: %.9f milliseconds and result = %lf\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000,sum);*/
    printf("%.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);

    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sum = inner_p_8(vector1,vector2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    /*printf("Total time taken for step = 8: %.9f milliseconds and result = %lf\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000,sum);*/
     printf("%.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);


    clock_gettime(CLOCK_MONOTONIC, &t_start);
    sum = inner_p_16(vector1,vector2);
    clock_gettime(CLOCK_MONOTONIC, &t_stop);
    /*printf("Total time taken for step = 16: %.9f milliseconds and result = %lf\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000,sum);*/
     printf("%.6f\n",
           (((double)t_stop.tv_sec + 1.0e-9*t_stop.tv_nsec) - 
           ((double)t_start.tv_sec + 1.0e-9*t_start.tv_nsec))*1000);
    return 0;
}