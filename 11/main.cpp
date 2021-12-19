#include <fstream>
#include <iostream>
#include <string>
#include <vector>

static const std::string INPUT_FILE = "input.txt";
static const int STEPS = 100;
const int GRID_SIZE = 10;
const int FLASH_THRESHOLD = 9;
const int ON = -1;

auto get_grid() -> std::vector<std::vector<int>> {
  std::ifstream file;
  file.open(INPUT_FILE);

  std::string line;
  std::vector<std::vector<int>> grid(GRID_SIZE, std::vector<int>(GRID_SIZE, 1));
  int row_count = 0;
  while (std::getline(file, line)) {
    for (std::string::size_type i = 0; i < GRID_SIZE; i++) {
      char current = line[i];
      grid[row_count][i] = atoi(&current);
    }
    row_count++;
  }
  return grid;
}

void print_grid(const std::vector<std::vector<int>>& grid) {
  std::cout << "Grid: " << std::endl;

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      std::cout << grid[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

auto flash(std::vector<std::vector<int>>& grid, int i, int j) -> void {
  if (grid[i][j] == ON) return;

  grid[i][j] = ON;
  for (int i_next = i - 1; i_next <= i + 1; i_next++) {
    for (int j_next = j - 1; j_next <= j + 1; j_next++) {
      if (i_next < 0 || i_next >= GRID_SIZE) continue;
      if (j_next < 0 || j_next >= GRID_SIZE) continue;
      if (i == i_next && j == j_next) continue;
      if (grid[i_next][j_next] != ON) {
        grid[i_next][j_next]++;
        if (grid[i_next][j_next] > FLASH_THRESHOLD) flash(grid, i_next, j_next);
      }
    }
  }
}

auto simulate_step(std::vector<std::vector<int>>& grid) -> int {
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      grid[i][j]++;
    }
  }

  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] > FLASH_THRESHOLD) {
        flash(grid, i, j);
      }
    }
  }

  int flash_count = 0;
  for (int i = 0; i < GRID_SIZE; i++) {
    for (int j = 0; j < GRID_SIZE; j++) {
      if (grid[i][j] == ON) {
        flash_count++;
        grid[i][j] = 0;
      }
    }
  }

  return flash_count;
}

auto count_flashes(std::vector<std::vector<int>>& grid) {
  int flashes = 0;
  for (int i = 0; i < STEPS; i++) {
    flashes += simulate_step(grid);
  }
  return flashes;
}

auto main() -> int {
  std::vector<std::vector<int>> grid = get_grid();
  std::cout << "Initial board: ";
  print_grid(grid);
  int flashes = count_flashes(grid);
  std::cout << "Total flashes at step " << STEPS << ": " << flashes
            << std::endl;
  print_grid(grid);
}