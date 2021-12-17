#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static constexpr int row_size = 5;
static constexpr int col_size = 10;
static const std::string input_file = "input.txt";

std::vector<std::vector<int>> getGrid()
{
	std::ifstream file;
	file.open(input_file);

	std::vector<std::vector<int>> grid(row_size, std::vector<int>(col_size, 1));
	int row_count = 0;
	std::string line;
	while (std::getline(file, line))
	{
		for (std::string::size_type i = 0; i < col_size; i++)
		{
			char current = line[i];
			grid[row_count][i] = atoi(&current); // conversion done wrong, it's doing the exact inverse
		}
		row_count++;
	}

	return grid;
}

int main()
{
	const std::string input = "input.txt";

	const std::vector<std::vector<int>> grid = getGrid();
	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}
