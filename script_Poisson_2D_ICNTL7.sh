#!/bin/sh
make clean
make

matrixfilename="Poisson_2D/Poisson_2D.m"
rhsfilename="Poisson_2D/Poisson_2D_rhs.m"

outputdouble="result_Poisson2D_double_ICNTL7.txt"
outputfloat="result_Poisson2D_float_ICNTL7.txt"


#arguments à la suite: matrixfilename rhsfilename outputfilename sym(0,1,2) puis num du ICNTL et argument
for ICNTL7 in 0 2 3 4 5 6 7
do
	./mumps_test $matrixfilename $rhsfilename $outputdouble 0 7 $ICNTL7 >> script_Poisson_2D_ICNTL7.txt
	./smumps_test $matrixfilename $rhsfilename $outputfloat 0 7 $ICNTL7 >> script_Poisson_2D_ICNTL7.txt
done

