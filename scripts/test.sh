#!/bin/bash

# Declare collection of algorithms to run
declare -a algos=("ZhangShasha" "Saeed")

total=0
passed=0

# Compile the app with g++
g++ -o ted.exe -I./src/models -I./src/procedures *.cpp src/models/*.cpp src/procedures/*.cpp

# Loop through list of algorithms
for algo in "${algos[@]}"; do
    echo "Tests: $algo"
    # Loop through the test files
    for file in data/*.in; do
        # Get the file name without extension
        name=${file%.in}

    # Run the app with the input file and redirect the output to a file
    ./ted.exe < $file > output/$algo/${name##*/}.out $algo

    # Increment the total number of passed tests by one
    ((total++))

    # Compare the output file with the expected file
    diff output/$algo/${name##*/}.out output/expected/${name##*/}.out
    # Check the exit status of the diff command
    if [ $? -eq 0 ]; then
        # If the exit status is 0, the files are identical
        echo "Test $name passed"
        # Increment the number of passed tests for the algorithm by one
        ((passed++))
    else
        # If the exit status is not 0, the files are different
        echo "Test $name failed"
    fi

    done
done

# Calculate the percentage of passed tests for the algorithm
percentage=$(( passed * 100/total ))
# Print the number and percentage of passed tests for the command
echo

GREEN='\033[0;32m'
RED='\033[0;31m'
if [ $passed -eq $total ]; then
    echo -e "${GREEN}$passed / $total tests passed ($percentage%)"
    exit 0
else
    echo -e "${RED}$passed / $total tests passed ($percentage%)"
    exit 3
fi