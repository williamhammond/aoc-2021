
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <array>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <vector>

#define MAX_LINE_LENGTH 8192

auto main(int argc, char** argv) -> int {
  auto const* path = "input.txt";

  FILE* file = fopen(path, "r");

  if (file == nullptr) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};  // NOLINT
  int total = 0;
  while (fgets(line, MAX_LINE_LENGTH, file) != nullptr) {
    line[strcspn(line, "\n")] = 0;

    char* signals = strtok(line, "|");
    char* output = strtok(nullptr, "|");

    std::map<uint64_t, std::set<std::string>> lengthMap;
    char* signal = strtok(signals, " ");
    while (signal != nullptr) {
      std::set<std::string> chars;
      for (uint64_t i = 0; i < strlen(signal); i++) {
        std::string c = std::string(1, signal[i]);
        chars.insert(c);
      }
      lengthMap.insert(
          std::pair<uint64_t, std::set<std::string>>(strlen(signal), chars));
      signal = strtok(nullptr, " ");
    }

    char* digit = strtok(output, " ");
    std::string decoded;
    while (digit != nullptr) {
      uint64_t const length = strlen(digit);
      std::set<std::string> digitSet;
      for (uint64_t i = 0; i < strlen(digit); i++) {
        std::string c = std::string(1, digit[i]);
        digitSet.insert(c);
      }
      std::set<std::string> fourIntersections;
      std::set_intersection(
          digitSet.begin(), digitSet.end(), lengthMap.at(4).begin(),
          lengthMap.at(4).end(),
          std::inserter(fourIntersections, fourIntersections.begin()));
      std::set<std::string> twoIntersections;
      std::set_intersection(
          digitSet.begin(), digitSet.end(), lengthMap.at(2).begin(),
          lengthMap.at(2).end(),
          std::inserter(twoIntersections, twoIntersections.begin()));
      switch (length) {
        case 2:
          decoded.append("1");
          break;
        case 3:
          decoded.append("7");
          break;
        case 4:
          decoded.append("4");
          break;
        case 7:  // NOLINT
          decoded.append("8");
          break;
        case 5:  // NOLINT
          if (fourIntersections.size() == 2) {
            decoded.append("2");
          }
          if (fourIntersections.size() == 3) {
            if (twoIntersections.size() == 2) {
              decoded.append("3");
            }
            if (twoIntersections.size() == 1) {
              decoded.append("5");
            }
          }
          break;
        case 6:  // NOLINT
          if (fourIntersections.size() == 4) {
            decoded.append("9");
          }
          if (fourIntersections.size() == 3) {
          if (fourIntersections.size() == 3) {
            if (twoIntersections.size() == 1) {
              decoded.append("6");
            }
            if (twoIntersections.size() == 2) {
              decoded.append("0");
            }
          }
          break;
        default:
          fprintf(stderr, "Invalid digit %lld \n", length);
          exit(EXIT_FAILURE);
      }
      digit = strtok(nullptr, " ");
    }
    total += atoi(decoded.c_str());
  }

  printf("Result: %d\n", total);

  if (fclose(file) != 0) {
    perror(path);
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
