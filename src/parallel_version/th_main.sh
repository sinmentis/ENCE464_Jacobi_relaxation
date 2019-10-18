#!/bin/sh

#Display greeting
echo ""
echo " #########Parallel Testing Begain#########"
echo " This testing script is for ENCE464 time analysis"
echo " It will analysis the time cost with different array size in different optimization command"
echo " Author: Shun Lyu"
echo ""

# Read from user input
echo "Take Notes, [ENTER] to start"
read notes
echo "===== START ====="

# Open CPU monitor
gnome-terminal -e "top -d 1"

# Run the code
for core in 7 8
do
	echo "===== CORE number = $core ====="
	for size in 101 201 301 401 501 601 701 801
	do
		echo "===== Array Size = $size ====="
		./poisson_test $size 500 $core
		wait
	done
done
