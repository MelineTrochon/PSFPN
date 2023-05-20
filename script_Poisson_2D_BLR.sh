#!/bin/sh



matrixfilename="Poisson_2D/Poisson_2D.m"
rhsfilename="Poisson_2D/Poisson_2D_rhs.m"

outputdouble="result_Poisson2D_double_BLR.txt"
outputfloat="result_Poisson2D_float_BLR.txt"


for ICNTL35 in 1 2 3
do
	for CNTL7 in 0 0.1 0.01 0.001 0.0001
	do 
		./mumps_test $matrixfilename $rhsfilename $outputdouble 0 35 $ICNTL35 -c 7 $CNTL7 >> script_Poisson_2D_BLR.txt
		./smumps_test $matrixfilename $rhsfilename $outputfloat 0 35 $ICNTL35 -c 7 $CNTL7 >> script_Poisson_2D_BLR.txt
	done
done
