#!/bin/sh
make clean
make


matrixfilename="dielFilterV2real/dielFilterV2real.mtx"
rhsfilename="dielFilterV2real/dielFilterV2real_b.mtx"
outputfilename="result_dielFilter.txt"


#echo $matrixfilename
for ICNTL7 in 0 2 6 7
do
	./mumps_test $matrixfilename $rhsfilename $outputfilename $ICNTL7
done
