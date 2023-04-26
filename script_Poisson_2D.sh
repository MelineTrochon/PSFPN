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
	./mumps_test $matrixfilename $rhsfilename $outputdouble 2 7 $ICNTL7 >> script_Poisson_2D.txt
	./smumps_test $matrixfilename $rhsfilename $outputfloat 2 7 $ICNTL7 >> script_Poisson_2D.txt
done

outputdouble="result_Poisson2D_double_BLR.txt"
outputfloat="result_Poisson2D_float_BLR.txt"

for ICNTL36 in 0 1
do
	for ICNTL35 in 0 1 2 3
	do 
		./mumps_test $matrixfilename $rhsfilename $outputdouble 2 36 $ICNTL36 35 $ICNTL35 >> script_Poisson_2D.txt
		./smumps_test $matrixfilename $rhsfilename $outputfloat 2 36 $ICNTL36 35 $ICNTL35 >> script_Poisson_2D.txt
	done
done
