#!/bin/bash
make clean
make


matrixfilename="Poisson_2D.m"
rhsfilename="Poisson_2D_rhs.m"


echo $matrixfilename
for ICNTL7 in 1 2 3
do
	./mumps_test $matrixfilename $rhsfilename
done
