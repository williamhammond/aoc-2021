
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CRAB_COUNT 2048
#define MAX_LINE_LENGTH 8192

int main(int argc, char** argv) {
  char* path = "test.txt";

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};
  int crabsPositions[MAX_CRAB_COUNT] = {0};
  int crabCount = 0;
  if (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    char* token = strtok(line, ",");
    while (token) {
      int position = atoi(token);
      crabsPositions[crabCount] = position;
      token = strtok(NULL, ",");
      crabCount++;
    }
  }

  unsigned long long differences[MAX_CRAB_COUNT][MAX_CRAB_COUNT] = {0};
  for (int i = 0; i < crabCount - 1; i++) {
    for (int j = i + 1; j < crabCount; j++) {
      unsigned long long cost = 0;
      unsigned long long difference =
          abs(crabsPositions[i] - crabsPositions[j]);

      for (unsigned long long step = 1; step <= difference; step++) {
        cost += step;
      }

      differences[i][j] = cost;
      differences[j][i] = cost;
    }
  }
  unsigned long long answer = LLONG_MAX;
  for (int i = 0; i < crabCount; i++) {
    unsigned long long sum = 0;
    for (int j = 0; j < crabCount; j++) {
      sum += (differences[j][i]);
    }
    if (sum < answer) {
      answer = sum;
    }
  }
  printf("Answer: %llu\n", answer);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
