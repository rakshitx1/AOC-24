#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <sstream>
#include <string>

int main()
{
	std::ifstream file("Input.txt"); // Open the file
	std::unordered_map<int, std::unordered_set<int>> before_map;
	std::vector<std::vector<int>> updates;

	std::string line;
	bool is_rules_section = true;

	// Read the file line by line
	while (std::getline(file, line))
	{
		// Check if the line contains a pipe (|) or a comma (,)
		if (line.find('|') != std::string::npos)
		{
			// This line is a rule (X|Y)
			int before, after;
			std::stringstream ss(line);
			char delimiter;
			ss >> before >> delimiter >> after;
			before_map[before].insert(after);
		}
		else if (line.find(',') != std::string::npos)
		{
			// This line is an update (list of page numbers)
			std::vector<int> update;
			std::stringstream ss(line);
			int page;
			while (ss >> page)
			{
				update.push_back(page);
				if (ss.peek() == ',')
				{
					ss.ignore();
				}
			}
			updates.push_back(update);
		}
	}

	// Close the file
	file.close();

	int count = 0;

	// Output the updates and their validation status
	for (size_t i = 0; i < updates.size(); ++i)
	{
		const std::vector<int> &update = updates[i];
		bool is_valid = true;

		for (int j = update.size() - 1; j >= 0; j--)
		{
			for (int k = j - 1; k >= 0; k--)
			{
				if (j != k)
				{
					if (before_map.find(update[j]) != before_map.end())
					{
						if (before_map[update[j]].find(update[k]) != before_map[update[j]].end())
						{
							is_valid = false;
							break;
						}
					}
				}
			}
			if (!is_valid)
			{
				break;
			}
		}

		if (is_valid)
		{
			count += update[(update.size() - 1) / 2];
		}
	}

	std::cout << "Sum of the middle elements of valid updates: " << count << std::endl;

	return 0;
}
