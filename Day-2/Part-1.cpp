#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

bool isSafe(const std::vector<int>& list) {
	if (list.size() < 2) return false;

	bool order = list[0] < list[1];
	for (size_t i = 0; i < list.size() - 1; i++) {
		int diff = std::abs(list[i + 1] - list[i]);
		if (diff < 1 || diff > 3) {
			return false;
		}

		bool newOrder = list[i] < list[i + 1];
		if (newOrder != order) {
			return false;
		}
	}
	return true;
}

int main() {
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<int> list;

	int safeReports = 0;

	std::string line;
	// Read each line from the file
	while (std::getline(inputFile, line)) {
		list.clear(); // Clear the list for each line
		std::istringstream stream(line); // Create a stream for the line
		int num;

		// Extract integers from the line
		while (stream >> num) {
			list.push_back(num);
		}

		if (isSafe(list)) {
			safeReports++;
		}
	}

	inputFile.close();

	std::cout << "Safe reports: " << safeReports << std::endl;
}
