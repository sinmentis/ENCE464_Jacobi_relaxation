#!/bin/sh

#Display greeting
echo ""
echo " #########Parallel Testing Begain#########"
echo " This testing script is for ENCE464 time analysis"
echo " It will analysis the time cost with different array size in different optimization command"
echo " Author: Shun Lyu"
echo ""

# Take notes
echo "Take Notes, [ENTER] to start"
read notes

# Open CPU monitor
gnome-terminal -e "top -d 1"

# Run the code
for op in 0 1 2 3
do
	echo " ======= Clean Done ======="
	rm poisson.o
    echo " ======= make Done ======="
  	g++ -fopenmp -O$op -std=c++11 -g3 -o poisson_test poisson_test.cpp poisson.cpp
	echo " ======= Run op=o$op ======="
    for size in 100 200 300 400 500 600 700 800
	do
		echo " ------- size number = $numiter"
		./poisson_test $size 500 4
		wait
	done
done
