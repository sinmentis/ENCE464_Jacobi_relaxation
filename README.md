Before using main.sh Remember to do this first:
    $ chmod 777 main.sh

Geany Command:

    build|Compile: g++ -fopenmp -O0 -std=c++11 -g3 -o %e %f poisson.cpp
    Execute:       "./%e" 300 40 3

Cachegrind Command:
valgrind --tool=cachegrind ./poisson_test 300 300 4


TODO:
    1. Two algorithm for Openmp: Section and parallel
    2. Do time analysis individually:
        Core number 
        Array size 
        Number of loop 
    3. Cache analysis

TOASK:
    1. Multithread or Multicore?
    2. The aiming of the assignment, Speed or memory
    3. How to do cache analysis
