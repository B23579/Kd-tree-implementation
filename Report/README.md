
# Process to run all the program we provided 

Our OpenMP  and hybrid OpenMP + MPI program were writing in `c++`. On login node, compile each program by runing the following file. 

```
  ./compile.sh
```
To submit the job on the computer node, run the following syntax for OpenMP program :

```
qsub kdtree.pbs
```
and the following for hybrid program :

```
qsub hybrid.pbs
```
To run the serial code, set the number of thread to 1 using  in ` kdtree.cpp` in the following syntax `omp_set_num_threads(1);`. 
By changing that value, we increase and reduce the number of thread. 

