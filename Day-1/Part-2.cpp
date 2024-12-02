#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

int main() {
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open()) {
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	std::vector<int> leftList, rightList;

	// Read the pairs from the file
	int num1, num2;
	while (inputFile >> num1 >> num2) {
		leftList.push_back(num1);
		rightList.push_back(num2);
	}
	inputFile.close();

	// Count occurrences in the right list using a hash map
	std::unordered_map<int, int> rightCount;
	for (const auto& num : rightList) {
		rightCount[num]++;
	}

	// Calculate the similarity score
	int similarityScore = 0;
	for (const auto& num : leftList) {
		similarityScore += num * rightCount[num];
	}

	// Output the result
	std::cout << "Similarity Score: " << similarityScore << std::endl;
}
