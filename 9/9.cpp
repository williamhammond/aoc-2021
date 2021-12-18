#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static constexpr int row_size = 5;
static constexpr int col_size = 10;
static const std::string input_file = "input.txt";

std::vector<std::vector<int>> get_grid() {
  std::ifstream file;
  file.open(input_file);

  std::vector<std::vector<int>> grid(row_size, std::vector<int>(col_size, 1));
  int row_count = 0;
  std::string line;
  while (std::getline(file, line)) {
    for (std::string::size_type i = 0; i < col_size; i++) {
      char current = line[i];
      grid[row_count][i] = atoi(&current);
    }
    row_count++;
  }

  return grid;
}

void print_grid(const std::vector<std::vector<int>>& grid) {
  std::cout << "Input: " << std::endl;

  for (int i = 0; i < row_size; i++) {
    for (int j = 0; j < col_size; j++) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

uint64_t solve(const std::vector<std::vector<int>>& grid) {
  int result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      const bool is_left_higher = (j - 1 == -1) || grid[i][j - 1] > grid[i][j];
      const bool is_right_higher =
          (j + 1 == grid[i].size()) || grid[i][j + 1] > grid[i][j];
      const bool is_up_higher = (i - 1 == -1) || grid[i - 1][j] > grid[i][j];
      const bool is_down_higher =
          (i + 1 == grid.size()) || grid[i + 1][j] > grid[i][j];
      const bool is_low_point =
          is_left_higher && is_right_higher && is_up_higher && is_down_higher;

      if (is_low_point) {
        result += grid[i][j] + 1;
      }
    }
  }
  return result;
}

int main() {
  const std::vector<std::vector<int>> grid = get_grid();

  print_grid(grid);

  const uint64_t result = solve(grid);
  std::cout << "Result is: " << result << std::endl;
}
