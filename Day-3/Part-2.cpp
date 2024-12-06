#include <fstream>
#include <iostream>
#include <regex>
#include <string>

int main()
{
	// Open the input file
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open())
	{
		std::cerr << "Error opening file!" << std::endl;
		return 1;
	}

	int result = 0;
	bool isEnabled = true; // Initially, mul instructions are enabled

	std::string line;

	// Regular expressions for patterns
	std::regex mulPattern(R"(mul\((\d{1,3}),(\d{1,3})\))");
	std::regex doPattern(R"(do\(\))");
	std::regex dontPattern(R"(don't\(\))");

	// Read the file line by line
	while (std::getline(inputFile, line))
	{
		std::sregex_iterator current(line.begin(), line.end(), mulPattern);
		std::sregex_iterator end;

		std::sregex_iterator doCheck(line.begin(), line.end(), doPattern);
		std::sregex_iterator dontCheck(line.begin(), line.end(), dontPattern);

		// Create a single iterator to process instructions in sequence
		size_t pos = 0; // Current position in the line
		while (pos < line.size())
		{
			size_t nextMul = std::string::npos;
			size_t nextDo = std::string::npos;
			size_t nextDont = std::string::npos;

			// Find the positions of the next occurrences of each instruction
			if (current != end)
				nextMul = (*current).position();
			if (doCheck != std::sregex_iterator())
				nextDo = (*doCheck).position();
			if (dontCheck != std::sregex_iterator())
				nextDont = (*dontCheck).position();

			// Determine the next instruction to process
			if (nextDo < nextMul && nextDo < nextDont)
			{
				isEnabled = true; // Enable mul instructions
				pos = nextDo + (*doCheck).length();
				++doCheck;
			}
			else if (nextDont < nextMul && nextDont < nextDo)
			{
				isEnabled = false; // Disable mul instructions
				pos = nextDont + (*dontCheck).length();
				++dontCheck;
			}
			else if (nextMul < nextDo && nextMul < nextDont)
			{
				if (isEnabled)
				{
					int X = std::stoi((*current)[1].str());
					int Y = std::stoi((*current)[2].str());
					result += X * Y;
				}
				pos = nextMul + (*current).length();
				++current;
			}
			else
			{
				break;
			}
		}
	}

	// Close the input file
	inputFile.close();

	// Output the final result
	std::cout << "Result: " << result << std::endl;

	return 0;
}
