#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <vector>

static constexpr int row_size = 100;
static constexpr int col_size = 100;
static const std::string input_file = "input.txt";

std::vector<std::vector<int>> get_grid()
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
			grid[row_count][i] = atoi(&current);
		}
		row_count++;
	}

	return grid;
}

void print_grid(const std::vector<std::vector<int>>& grid)
{
	std::cout << "Input: " << std::endl;

	for (int i = 0; i < row_size; i++)
	{
		for (int j = 0; j < col_size; j++)
		{
			std::cout << grid[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int find_lowest_points(const std::vector<std::vector<int>>& grid)
{
	int result = 0;
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			const bool is_left_higher = (j - 1 == -1) || grid[i][j - 1] > grid[i][j];
			const bool is_right_higher =
				(j + 1 == grid[i].size()) || grid[i][j + 1] > grid[i][j];
			const bool is_up_higher = (i - 1 == -1) || grid[i - 1][j] > grid[i][j];
			const bool is_down_higher =
				(i + 1 == grid.size()) || grid[i + 1][j] > grid[i][j];
			const bool is_low_point =
				is_left_higher && is_right_higher && is_up_higher && is_down_higher;

			if (is_low_point)
			{
				result += grid[i][j] + 1;
			}
		}
	}
	return result;
}

uint32_t flood_fill(std::vector<std::vector<int>>& grid, uint32_t initial_row,
                    uint32_t initial_column)
{
	if (initial_row >= grid.size() || initial_column >= grid[initial_row].size() ||
		grid[initial_row][initial_column] == 9)
		return 0;

	uint32_t result = 0;
	std::queue<std::pair<uint32_t, uint32_t>> queue;
	queue.push(std::make_pair(initial_row, initial_column));
	while (!queue.empty())
	{
		auto [current_row, current_column] = queue.front();
		queue.pop();
		if (current_row + 1 < grid.size() && grid[current_row + 1][current_column] != 9)
		{
			grid[current_row + 1][current_column] = 9;
			result++;
			queue.push(std::make_pair(current_row + 1, current_column));
		}
		if (current_row > 0 && grid[current_row - 1][current_column] != 9)
		{
			grid[current_row - 1][current_column] = 9;
			result++;
			queue.push(std::make_pair(current_row - 1, current_column));
		}
		if (current_column + 1 < grid[current_row].size() && grid[current_row][current_column + 1] != 9)
		{
			grid[current_row][current_column + 1] = 9;
			result++;
			queue.push(std::make_pair(current_row, current_column + 1));
		}
		if (current_column > 0 && grid[current_row][current_column - 1] != 9)
		{
			grid[current_row][current_column - 1] = 9;
			result++;
			queue.push(std::make_pair(current_row, current_column - 1));
		}
	}
	return result;
}

int find_basins(std::vector<std::vector<int>>& grid)
{
	std::vector<uint32_t> sizes;
	for (size_t row = 0; row < grid.size(); row++)
	{
		for (size_t column = 0; column < grid[row].size(); column++)
		{
			uint32_t size = flood_fill(grid, row, column);
			if (size != 0)
			{
				sizes.push_back(size);
			}
		}
	}
	std::cout << "Total of non-zero sized basins: " << sizes.size() << "\n";
	std::ranges::sort(sizes, std::greater<>());
	return sizes[0] * sizes[1] * sizes[2];
}

int main()
{
	std::vector<std::vector<int>> grid = get_grid();

	const int lowest_point_score = find_lowest_points(grid);
	std::cout << "Part 1: " << lowest_point_score << std::endl;

	const int basin_score = find_basins(grid);
	std::cout << "Part 2: " << basin_score << std::endl;
}
