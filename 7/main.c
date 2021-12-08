
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CRAB_COUNT 2048
#define MAX_LINE_LENGTH 8192

int fuel(int n) { return (n * (n + 1)) / 2; }

int main(int argc, char** argv) {
  char* path = "input.txt";

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};
  int crabsPositions[MAX_CRAB_COUNT] = {0};
  int crabCount = 0;
  int mean = 0;
  if (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    char* token = strtok(line, ",");
    while (token) {
      int position = atoi(token);
      crabsPositions[crabCount] = position;
      mean += position;
      token = strtok(NULL, ",");
      crabCount++;
    }
  }

  mean = mean / crabCount;  // NOLINT

  int sum = 0;
  for (int i = 0; i < crabCount; i++) {
    sum += fuel(abs(crabsPositions[i] - mean));
  }
  printf("Total fuel used: %d\n", sum);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
