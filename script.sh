#!/bin/sh
make clean
make


matrixfilename="Poisson_3D/Poisson_3D.m"
rhsfilename="Poisson_3D/Poisson_3D_rhs.m"
outputfilename="result_Poisson3D_double.txt"


#arguments à la suite: matrixfilename rhsfilename outputfilename sym(0,1,2) ICNTL7
#echo $matrixfilename
for ICNTL7 in 0 2 3 4 5 6 7
do
	./mumps_test $matrixfilename $rhsfilename $outputfilename 2 $ICNTL7
done



matrixfilename="Poisson_3D/Poisson_3D.m"
rhsfilename="Poisson_3D/Poisson_3D_rhs.m"
outputfilename="result_Poisson3D_float.txt"


#arguments à la suite: matrixfilename rhsfilename outputfilename sym(0,1,2) ICNTL7
#echo $matrixfilename
for ICNTL7 in 0 2 3 4 5 6 7
do
	./smumps_test $matrixfilename $rhsfilename $outputfilename 2 $ICNTL7
done