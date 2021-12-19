#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

static const std::string input_file = "input.txt";
static const std::map<char, int> scores = {
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
static const std::map<char, char> tokenAssociation = {
    {'(', ')'}, {')', '('}, {'[', ']'}, {']', '['},
    {'{', '}'}, {'}', '{'}, {'<', '>'}, {'>', '<'}};

auto get_nav_lines() -> std::vector<std::string> {
  std::ifstream file;
  file.open(input_file);

  std::string line;
  std::vector<std::string> lines;
  while (std::getline(file, line)) {
    lines.push_back(line);
  }
  return lines;
}

auto is_open_token(const char& token) -> bool {
  return token == '{' || token == '(' || token == '<' || token == '[';
}

auto calc_illegal_syntax_score(const std::vector<std::string>& lines) -> int {
  int result = 0;
  std::stack<char> stack;
  for (std::string line : lines) {
    for (char token : line) {
      if (is_open_token(token)) {
        stack.push(token);
      } else {
        char closingToken = stack.top();
        stack.pop();
        if (tokenAssociation.at(token) != closingToken) {
          result += scores.at(token);
          break;
        }
      }
    }
  }
  return result;
}

auto main() -> int {
  std::vector<std::string> lines = get_nav_lines();
  int score = calc_illegal_syntax_score(lines);
  std::cout << "Score is: " << score << std::endl;
}