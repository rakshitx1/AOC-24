#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool checkNorth(std::vector<std::string> grid, int i, int j)
{
	if (i - 3 >= 0)
	{
		if (grid[i][j] == 'X' && grid[i - 1][j] == 'M' && grid[i - 2][j] == 'A' && grid[i - 3][j] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkSouth(std::vector<std::string> grid, int i, int j)
{
	if (i + 3 < grid.size())
	{
		if (grid[i][j] == 'X' && grid[i + 1][j] == 'M' && grid[i + 2][j] == 'A' && grid[i + 3][j] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkEast(std::vector<std::string> grid, int i, int j)
{
	if (j + 3 < grid[0].size())
	{
		if (grid[i][j] == 'X' && grid[i][j + 1] == 'M' && grid[i][j + 2] == 'A' && grid[i][j + 3] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkWest(std::vector<std::string> grid, int i, int j)
{
	if (j - 3 >= 0)
	{
		if (grid[i][j] == 'X' && grid[i][j - 1] == 'M' && grid[i][j - 2] == 'A' && grid[i][j - 3] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkNE(std::vector<std::string> grid, int i, int j)
{
	if (i - 3 >= 0 && j + 3 < grid[0].size())
	{
		if (grid[i][j] == 'X' && grid[i - 1][j + 1] == 'M' && grid[i - 2][j + 2] == 'A' && grid[i - 3][j + 3] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkNW(std::vector<std::string> grid, int i, int j)
{
	if (i - 3 >= 0 && j - 3 >= 0)
	{
		if (grid[i][j] == 'X' && grid[i - 1][j - 1] == 'M' && grid[i - 2][j - 2] == 'A' && grid[i - 3][j - 3] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkSE(std::vector<std::string> grid, int i, int j)
{
	if (i + 3 < grid.size() && j + 3 < grid[0].size())
	{
		if (grid[i][j] == 'X' && grid[i + 1][j + 1] == 'M' && grid[i + 2][j + 2] == 'A' && grid[i + 3][j + 3] == 'S')
		{
			return true;
		}
	}

	return false;
}

bool checkSW(std::vector<std::string> grid, int i, int j)
{
	if (i + 3 < grid.size() && j - 3 >= 0)
	{
		if (grid[i][j] == 'X' && grid[i + 1][j - 1] == 'M' && grid[i + 2][j - 2] == 'A' && grid[i + 3][j - 3] == 'S')
		{
			return true;
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
			if (checkNorth(grid, i, j))
			{
				count++;
			}

			if (checkSouth(grid, i, j))
			{
				count++;
			}

			if (checkEast(grid, i, j))
			{
				count++;
			}

			if (checkWest(grid, i, j))
			{
				count++;
			}

			if (checkNE(grid, i, j))
			{
				count++;
			}

			if (checkNW(grid, i, j))
			{
				count++;
			}

			if (checkSE(grid, i, j))
			{
				count++;
			}

			if (checkSW(grid, i, j))
			{
				count++;
			}
		}
	}

	std::cout << "XMAS appears " << count << " times." << std::endl;
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
