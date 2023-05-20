#!/bin/sh



matrixfilename="Poisson_3D/Poisson_3D.m"
rhsfilename="Poisson_3D/Poisson_3D_rhs.m"

outputdouble="result_Poisson3D_double_BLR.txt"
outputfloat="result_Poisson3D_float_BLR.txt"

for ICNTL35 in 1 2 3
do
	for CNTL7 in 0 0.1 0.01 0.001 0.0001
	do 
		./mumps_test $matrixfilename $rhsfilename $outputdouble 0 35 $ICNTL35 -c 7 $CNTL7 >> script_Poisson_3D_BLR.txt
		./smumps_test $matrixfilename $rhsfilename $outputfloat 0 35 $ICNTL35 -c 7 $CNTL7 >> script_Poisson_3D_BLR.txt
	done
done
