#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <tuple>

const std::vector<std::pair<int, int>> directions = {
	{-1, 0}, // Up
	{0, 1},	 // Right
	{1, 0},	 // Down
	{0, -1}	 // Left
};

bool simulateGuard(const std::vector<std::string> &map, std::pair<int, int> startPos, char startDir)
{
	int rows = map.size();
	int cols = map[0].size();

	int xi = startPos.first, yi = startPos.second;

	int direction;
	if (startDir == '^')
	{
		direction = 0;
	}
	else if (startDir == '>')
	{
		direction = 1;
	}
	else if (startDir == 'v')
	{
		direction = 2;
	}
	else
	{
		direction = 3;
	}

	std::set<std::pair<int, int>> visitedPositions;
	int numberOfCollisions = 0;
	bool loop = false;

	std::set<std::tuple<int, int, int>> visitedStates;

	while (true)
	{
		int dx = directions[direction].first;
		int dy = directions[direction].second;

		int xf = xi + dx, yf = yi + dy;

		if (xf < 0 || yf < 0 || xf >= rows || yf >= cols)
		{
			break;
		}

		if (map[xf][yf] == '#')
		{
			if (visitedStates.count(std::make_tuple(xi, yi, direction)))
			{
				loop = true;
				break;
			}

			visitedStates.insert(std::make_tuple(xi, yi, direction));

			direction = (direction + 1) % 4;
		}
		else
		{
			xi = xf;
			yi = yf;
		}
	}

	return loop;
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
	std::vector<std::string> map;
	std::pair<int, int> startPos;
	char startDir;

	int row = 0;
	while (getline(inputFile, line))
	{
		map.push_back(line);
		if (line.find('^') != std::string::npos)
		{
			startPos = {row, line.find('^')};
			startDir = '^';
		}
		else if (line.find('>') != std::string::npos)
		{
			startPos = {row, line.find('>')};
			startDir = '>';
		}
		else if (line.find('v') != std::string::npos)
		{
			startPos = {row, line.find('v')};
			startDir = 'v';
		}
		else if (line.find('<') != std::string::npos)
		{
			startPos = {row, line.find('<')};
			startDir = '<';
		}
		row++;
	}

	inputFile.close();

	int loops = 0;

	for(int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map[0].size(); j++)
		{
			if(map[i][j] == '^' || map[i][j] == '>' || map[i][j] == 'v' || map[i][j] == '<' || map[i][j] == '#')
			{
				continue;
			}
			else
			{
				std::vector<std::string> newMap = map;
				newMap[i][j] = '#';

				if(simulateGuard(newMap, startPos, startDir))
				{
					loops++;
				}
			}
		}
	}

	std::cout << "Number of loops: " << loops << std::endl;

	return 0;
}
