#!/bin/bash

# Setting up trap to handle exit status
trap 'EXIT_STATUS=$?; if [ $EXIT_STATUS -eq 0 ]; then echo -e "\033[32mProgram exited successfully.\033[0m"; else echo -e "\033[31mProgram exited with status $EXIT_STATUS.\033[0m"; fi' EXIT

# Get the directory where this script is located
SCRIPT_DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" >/dev/null 2>&1 && pwd )"

# Navigate to the project directory
cd "$SCRIPT_DIR" || { echo -e "\033[31mFailed to navigate to the script directory.\033[0m"; exit 1; }

# ask for user input
echo -e "\033[33mPlease enter the Day\033[0m"
read -r day

echo -e "\033[33mPlease enter the Part\033[0m"
read -r part

# check if the directory and file exists
if [ ! -d "Day-$day" ] || [ ! -f "Day-$day/Part-$part.cpp" ]; then
    echo -e "\033[31mDay $day Part $part does not exist.\033[0m"
    exit 1
fi

# print which day and part is being run
echo ""
echo -e "\033[33mRunning Day $day Part $part\033[0m"

# navigate to the directory and compile the file
cd Day-$day
clang++ -std=c++17 Part-$part.cpp -o Part-$part.out

# run the executable
time ./Part-$part.out

# remove the executable
rm Part-$part.out
