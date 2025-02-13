#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <mutex>
#include <string>
#include <queue>
#include <cmath>
#include <numeric>

// BFS state representation
struct State
{
	int index;
	long long value;
};

long long concatenate(long long a, long long b)
{
	long long multiplier = 1;
	while (multiplier <= b)
		multiplier *= 10;
	return a * multiplier + b;
}

bool canEvaluateToTarget(const std::vector<long long> &numbers, long long target)
{
	std::queue<State> q;
	q.push({0, numbers[0]}); // Start with the first number

	while (!q.empty())
	{
		State current = q.front();
		q.pop();

		if (current.index == numbers.size() - 1)
		{
			if (current.value == target)
				return true;
			continue;
		}

		long long nextNumber = numbers[current.index + 1];

		// Try addition
		q.push({current.index + 1, current.value + nextNumber});

		// Try multiplication
		q.push({current.index + 1, current.value * nextNumber});

		// Try concatenation
		q.push({current.index + 1, concatenate(current.value, nextNumber)});
	}

	return false;
}

// Worker function for each thread
void processEquations(const std::vector<std::string> &equations, size_t start, size_t end, long long &threadResult)
{
	threadResult = 0;

	for (size_t i = start; i < end; ++i)
	{
		const auto &eq = equations[i];
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

		if (canEvaluateToTarget(numbers, testValue))
		{
			threadResult += testValue;
		}
	}
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

	const size_t numThreads = std::thread::hardware_concurrency(); // Number of threads available
	size_t equationsPerThread = equations.size() / numThreads;
	std::vector<std::thread> threads;
	std::vector<long long> threadResults(numThreads, 0);

	// Launch threads
	for (size_t i = 0; i < numThreads; ++i)
	{
		size_t start = i * equationsPerThread;
		size_t end = (i == numThreads - 1) ? equations.size() : start + equationsPerThread;

		threads.emplace_back(processEquations, std::cref(equations), start, end, std::ref(threadResults[i]));
	}

	// Join threads
	for (auto &thread : threads)
	{
		thread.join();
	}

	// Sum up all thread results
	long long totalCalibrationResult = std::accumulate(threadResults.begin(), threadResults.end(), 0LL);

	std::cout << "Total calibration result: " << totalCalibrationResult << std::endl;
	return 0;
}
