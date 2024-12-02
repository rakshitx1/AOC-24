#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdlib>

int main() {
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<int> list1, list2;

	// Read the pairs from the file
	int num1, num2;
	while (inputFile >> num1 >> num2) {
		list1.push_back(num1);
		list2.push_back(num2);
	}
	inputFile.close();

	// Sort both lists in ascending order
	std::sort(list1.begin(), list1.end());
	std::sort(list2.begin(), list2.end());

	// Calculate the total distance
	int totalDistance = 0;
	for (size_t i = 0; i < list1.size(); ++i) {
		totalDistance += std::abs(list1[i] - list2[i]);
	}

	std::cout << "Total distance: " << totalDistance << std::endl;
}
