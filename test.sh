#!/bin/bash

# FILEPATH: /home/lithium/Projects/philosophers/test.sh
# make a test script for input into a program called "philosopers" that will take in 4 or 5 arguments
# run the program and check the output if it contains "ERROR" or "error" then it will print out the error
# if it does not contain "ERROR" or "error" then it will print out a check mark

# test the input parameters for the program the list of parameters are as follows with their requirements
# 1. number of philosophers (1 or max int) add a warning if the number is higher than 200
# 2. time to die (in milliseconds) (1 or max int)
# 3. time to eat (in milliseconds) (1 or max int)
# 4. time to sleep (in milliseconds) (1 or max int)
# 5. number of times each philosopher must eat (optional) (1 or max int)

# Function to print colored messages to the terminal
print_message() {
	local color=$1
	local message=$2
	echo -e "\033[${color}m${message}\033[0m"
}

# Function to test the philosophers program
test_philosophers() {
	local num_philosophers=$1
	local time_to_die=$2
	local time_to_eat=$3
	local time_to_sleep=$4
	local num_eat=$5

	echo -ne "\n\033[1mTesting $num_philosophers $time_to_die $time_to_eat $time_to_sleep $num_eat\033[0m\n"
	./philosophers $num_philosophers $time_to_die $time_to_eat $time_to_sleep $num_eat > test.txt
	if grep -q "ERROR" test.txt || grep -q "error" test.txt; then
		echo -ne "\033[31mERROR\033[0m\n"
	else
		echo -ne "\033[32m✅\033[0m\n"
	fi
}

# Function to test the philosophers program with a specific number of philosophers
test_philosophers_with_num() {
	local num_philosophers=$1
	local time_to_die=$2
	local time_to_eat=$3
	local time_to_sleep=$4
	local num_eat=$5

	print_message 33 "Running test with $num_philosophers philosophers"
	test_philosophers $num_philosophers $time_to_die $time_to_eat $time_to_sleep $num_eat
	echo ""
}

# Function to test the philosophers program with a range of philosophers
test_philosophers_with_range() {
	local start=$1
	local end=$2
	local time_to_die=$3
	local time_to_eat=$4
	local time_to_sleep=$5
	local num_eat=$6

	for (( i=$start; i<=$end; i++ ))
	do
		test_philosophers_with_num $i $time_to_die $time_to_eat $time_to_sleep $num_eat
	done
}

# Test 1: Minimum values
test_philosophers_with_num 1 1 1 1 ""

# Test 2: Maximum values
test_philosophers_with_num 200 2147483647 2147483647 2147483647 ""

# Test 3: High number of philosophers
test_philosophers_with_num 201 1000 1000 1000 ""

# Test 4: High time to die
test_philosophers_with_num 10 2147483647 1000 1000 ""

# Test 5: High time to eat
test_philosophers_with_num 10 1000 2147483647 1000 ""

# Test 6: High time to sleep
test_philosophers_with_num 10 1000 1000 2147483647 ""

# Test 7: All values are equal
test_philosophers_with_num 5 1000 1000 1000 ""

# Test 8: Optional argument not provided
test_philosophers_with_num 5 1000 1000 1000 ""

# Test 9: Optional argument provided
test_philosophers_with_num 5 1000 1000 1000 10

# Test 10: Zero values
test_philosophers_with_num 0 0 0 0 ""

# Test 11: Negative values
test_philosophers_with_num -5 -1000 -1000 -1000 ""

# Test 12-21: Range of philosophers
test_philosophers_with_range 1 10 1000 1000 1000 ""
echo ""

# Print error message if any tests failed
if grep -q "ERROR" test.txt || grep -q "error" test.txt; then
	print_message 31 "Some tests failed"
else
	print_message 32 "All tests passed"
fi
