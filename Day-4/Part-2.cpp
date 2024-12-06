#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool X_MAS(std::vector<std::string> grid, int i, int j)
{
	if(i > 0 && j > 0 && i < grid.size() - 1 && j < grid[0].size() - 1)
	{
		if(grid[i][j] == 'A')
		{
			bool mas1 = false;
			bool mas2 = false;

			char LT = grid[i - 1][j - 1];
			char RT = grid[i - 1][j + 1];
			char LB = grid[i + 1][j - 1];
			char RB = grid[i + 1][j + 1];

			if((LT == 'M' && RB == 'S') || (LT == 'S' && RB == 'M'))
			{
				mas1 = 1;
			}

			if((RT == 'M' && LB == 'S') || (RT == 'S' && LB == 'M'))
			{
				mas2 = 1;
			}

			if (mas1 && mas2)
			{
				return true;
			}
		}
	}

	return false;
}

void findX_MAS(std::vector<std::string> grid)
{
	int count = 0;

	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[0].size(); j++)
		{
			if (X_MAS(grid, i, j))
			{
				count++;
			}
		}
	}

	std::cout << "X-MAS appears " << count << " times." << std::endl;
}

int main()
{
	// File input
	std::ifstream inputFile("Input.txt");
	if (!inputFile.is_open())
	{
		std::cerr << "Could not open the file!" << std::endl;
		return 1;
	}

	std::vector<std::string> grid;
	std::string line;

	// Read the file and populate the grid
	while (getline(inputFile, line))
	{
		grid.push_back(line);
	}

	// Close the file after reading
	inputFile.close();

	// Call the function to search for "XMAS"
	findX_MAS(grid);

	return 0;
}
