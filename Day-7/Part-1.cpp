#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <functional>

using MemoKey = std::pair<int, long long>;

struct MemoKeyHash
{
	size_t operator()(const MemoKey &key) const
	{
		return std::hash<int>()(key.first) ^ std::hash<long long>()(key.second);
	}
};

// Helper function to recursively evaluate expressions.
bool canEvaluateToTarget(const std::vector<long long> &numbers, int index, long long currentValue, long long target,
						 std::unordered_map<MemoKey, bool, MemoKeyHash> &memo)
{
	if (index == numbers.size())
	{
		return currentValue == target;
	}

	MemoKey key = {index, currentValue};
	if (memo.count(key))
	{
		return memo[key];
	}

	// Try adding the next number.
	bool addResult = canEvaluateToTarget(numbers, index + 1, currentValue + numbers[index], target, memo);

	// Try multiplying the next number.
	bool multiplyResult = canEvaluateToTarget(numbers, index + 1, currentValue * numbers[index], target, memo);

	memo[key] = addResult || multiplyResult;
	return memo[key];
}

int main()
{
	std::ifstream inputFile("Input.txt");
	if (!inputFile)
	{
		std::cerr << "Failed to open input file!" << std::endl;
		return 1;
	}

	std::string line;
	std::vector<std::string> equations;

	while (getline(inputFile, line))
	{
		equations.push_back(line);
	}

	long long totalCalibrationResult = 0;

	for (const auto &eq : equations)
	{
		size_t colonPos = eq.find(':');
		long long testValue;
		try
		{
			testValue = std::stoll(eq.substr(0, colonPos));
		}
		catch (const std::exception &e)
		{
			std::cerr << eq.substr(0, colonPos) << '\n';
			continue;
		}

		std::vector<long long> numbers;

		size_t start = colonPos + 2;
		size_t spacePos;
		while ((spacePos = eq.find(' ', start)) != std::string::npos)
		{
			numbers.push_back(std::stoll(eq.substr(start, spacePos - start)));
			start = spacePos + 1;
		}
		numbers.push_back(std::stoll(eq.substr(start)));

		// Use a memo table to store intermediate results.
		std::unordered_map<MemoKey, bool, MemoKeyHash> memo;
		if (canEvaluateToTarget(numbers, 1, numbers[0], testValue, memo))
		{
			totalCalibrationResult += testValue;
		}
	}

	std::cout << "Total calibration result: " << totalCalibrationResult << std::endl;
	return 0;
}
