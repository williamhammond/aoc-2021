#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <vector>

static const std::string INPUT_FILE = "input.txt";
static const std::string DELIMITER = "-";

enum CAVE_TYPE { SMALL, BIG, START, END };
static const char* cave_type_strings[] = {"small", "big", "start", "end"};

struct Cave {
  std::string name;
  CAVE_TYPE cave_type;
  std::vector<Cave*> tunnels;
};

auto get_cave_type(std::string cave_type) -> CAVE_TYPE {
  if (cave_type == "start") {
    return START;
  }
  if (cave_type == "end") {
    return END;
  }
  if (std::isupper(cave_type[0])) {
    return BIG;
  }
  if (std::islower(cave_type[0])) {
    return SMALL;
  }
  throw std::invalid_argument("Cave type invalid");
}

auto build_graph() -> Cave* {
  std::ifstream file;
  file.open(INPUT_FILE);

  std::string line;
  std::map<std::string, Cave*> caves;
  while (std::getline(file, line)) {
    size_t pos = line.find(DELIMITER);
    std::string a = line.substr(0, pos);
    line.erase(0, pos + DELIMITER.length());
    std::string b = line;

    if (!caves.contains(a)) {
      Cave* cave_a = new Cave;
      cave_a->cave_type = get_cave_type(a);
      cave_a->name = a;
      caves.emplace(a, cave_a);
    }
    if (!caves.contains(b)) {
      Cave* cave_b = new Cave;
      cave_b->cave_type = get_cave_type(b);
      cave_b->name = b;
      caves.emplace(b, cave_b);
    }
    Cave* cave_a;
    cave_a = caves.at(a);
    Cave* cave_b;
    cave_b = caves.at(b);

    caves.at(a)->tunnels.push_back(cave_b);
    caves.at(b)->tunnels.push_back(cave_a);
  }
  return caves.at("start");
}

auto neighbor_string(const Cave* cave) -> std::string {
  std::string result = "";
  if (cave->tunnels.empty()) return result;
  for (auto neighbor : cave->tunnels) {
    result += neighbor->name;
    result += ", ";
  }
  result.resize(result.size() - 2);
  return result;
}

auto print_cave(const Cave* cave) -> void {
  std::cout << "{Name: " << cave->name
            << ", Type: " << cave_type_strings[cave->cave_type] << ", "
            << "Neighbors:" << neighbor_string(cave) << "}" << std::endl;
}

int count_paths(Cave* cave, std::set<Cave*> visited, int part) {
  if (cave->cave_type == END) return 1;
  if (visited.contains(cave)) {
    if (cave->cave_type == START) return 0;
    if (cave->cave_type ==SMALL) {
      if (part == 1) return 0;
      else part = 1; 
    }
  }

  visited.insert(cave);
  int sum = 0;
  for (auto neighbor : cave->tunnels) {
    sum += count_paths(neighbor, visited, part);
  }
  return sum;
}

auto main() -> int {
  Cave* start = build_graph();
  std::set<Cave*> visited;
  std::cout << "Result: " << count_paths(start, visited, 2);
  return EXIT_SUCCESS;
}