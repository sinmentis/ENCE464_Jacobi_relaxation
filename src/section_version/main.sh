#!/bin/sh

#Display greeting
echo ""
echo "                        Section Testing Begain"
echo ""
var1="       Size:     "
var2="       Numiters: "

# Read from user input
echo "What is the size of the array?"
read size
echo "What is the number of the loop?"
read numiter
echo "Take notes [enter to start]"
read notes

# Display input result
echo ""
echo $var1$size$var2$numiter
echo ""

# Open CPU monitor
gnome-terminal -e "top -d 1"

# Run the code
for core in 1 2 3 4 5 6 7 8
do
    ./poisson_test $size $numiter $core
    wait
done
