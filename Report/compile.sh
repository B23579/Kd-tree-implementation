#!/bin/bash

module load openmpi-4.1.1+gnu-9.3.0

gc++ -fopenmp kdtree.cpp -o kd
mpic++ -fopenmp kdtreehybrid.cpp -o kdH
