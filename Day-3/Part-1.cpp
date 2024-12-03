#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <regex>

int main() {
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	int Result = 0;
	std::string line;
	
	// Define the regular expression pattern to match 'mul(X,Y)' where X and Y are 1-3 digit numbers
	std::regex pattern(R"(mul\((\d{1,3}),(\d{1,3})\))");

	// Iterate through each line of the file
	while (std::getline(inputFile, line)) {
		// Use regex_iterator to find all matches in the line
		std::sregex_iterator begin(line.begin(), line.end(), pattern);
		std::sregex_iterator end;

		// Iterate over all matches
		for (std::sregex_iterator i = begin; i != end; ++i) {
			// Extract X and Y values
			int X = std::stoi((*i)[1].str());
			int Y = std::stoi((*i)[2].str());

			// Output values for debugging (optional)
			std::cout << "X: " << X << ", Y: " << Y << std::endl;

			// Add the product of X and Y to the result
			Result += X * Y;
		}
	}

	// Output the final result
	std::cout << "Result: " << Result << std::endl;

	return 0;
}
