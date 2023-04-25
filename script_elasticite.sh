#!/bin/sh
make clean
make


matrixfilename="elasticite/elasticite_2D.m"
rhsfilename="elasticite/elasticite_2D_rhs.m"
outputfilename="result_elasticite2D_double.txt"


#arguments à la suite: matrixfilename rhsfilename outputfilename sym(0,1,2) ICNTL7
#echo $matrixfilename
for ICNTL7 in 0 2 3 4 5 6 7
do
	./mumps_test $matrixfilename $rhsfilename $outputfilename 0 $ICNTL7
done



matrixfilename="elasticite/elasticite_2D.m"
rhsfilename="elasticite/elasticite_2D_rhs.m"
outputfilename="result_elasticite2D_single.txt"


#arguments à la suite: matrixfilename rhsfilename outputfilename sym(0,1,2) ICNTL7
#echo $matrixfilename
for ICNTL7 in 0 2 3 4 5 6 7
do
	./smumps_test $matrixfilename $rhsfilename $outputfilename 0 $ICNTL7
done