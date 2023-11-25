#!/bin/bash

THREADS=(1 2 3 4 5 6)

make 

for thread in ${THREADS[@]}; do
    export OMP_NUM_THREADS=$thread
    echo "Threads num = $thread"
    
    ./stencil_1D_SEQ 10000 20000 >> "computation.txt"
    ./stencil_2D_SEQ 3000 3000 >> "computation2.txt"
    ./mat_vec_SEQ 25000 10000 >> "computation3.txt"
    
done
make clean

