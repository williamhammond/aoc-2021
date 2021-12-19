#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>

static const std::string input_file = "input.txt";
static const std::map<char, int> corruptTokenScores = {
    {')', 3}, {']', 57}, {'}', 1197}, {'>', 25137}};
static const std::map<char, int> repairedSyntaxScores = {
    {')', 1}, {']', 2}, {'}', 3}, {'>', 4}};
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

auto get_repair_strings(const std::vector<std::string>& lines)
    -> std::vector<std::string> {
  std::vector<std::string> result;
  for (std::string line : lines) {
    std::stack<char> stack;
    bool is_corrupt = false;
    for (char token : line) {
      if (is_open_token(token)) {
        stack.push(token);
      } else {
        char closingToken = stack.top();
        stack.pop();
        if (tokenAssociation.at(token) != closingToken) {
          is_corrupt = true;
          // Skipping corrupted line
          break;
        }
      }
    }
    if (!is_corrupt) {
      std::string complete;
      while (!stack.empty()) {
        complete += tokenAssociation.at(stack.top());
        stack.pop();
      }
      result.push_back(complete);
    }
  }
  return result;
}

auto calc_repair_score(std::string repair_string) -> uint64_t {
  uint64_t score = 0;
  for (char token : repair_string) {
    score *= 5;
    score += repairedSyntaxScores.at(token);
  }
  return score;
}

auto calc_average_repair_score(std::vector<std::string> repair_strings) -> uint64_t{
  std::vector<uint64_t> scores;
  for (std::string repair_string : repair_strings) {
    scores.push_back(calc_repair_score(repair_string));
  }
  std::sort(scores.begin(), scores.end());
  return scores[scores.size() / 2];
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
          result += corruptTokenScores.at(token);
          break;
        }
      }
    }
  }
  return result;
}

auto main() -> int {
  std::vector<std::string> lines = get_nav_lines();
  auto repair_strings = get_repair_strings(lines);
  auto score = calc_average_repair_score(repair_strings);
  std::cout << "Score is: " << score << std::endl;
}