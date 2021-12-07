
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
  char* path = "input.txt";

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

  int differences[MAX_CRAB_COUNT][MAX_CRAB_COUNT] = {0};
  for (int i = 0; i < crabCount - 1; i++) {
    for (int j = i + 1; j < crabCount; j++) {
      differences[i][j] = abs(crabsPositions[i] - crabsPositions[j]);
      differences[j][i] = abs(crabsPositions[i] - crabsPositions[j]);
    }
  }
  int answer = INT_MAX;
  for (int i = 0; i < crabCount; i++) {
    int sum = 0;
    for (int j = 0; j < crabCount; j++) {
      sum += (differences[j][i]);
    }
    if (sum < answer) {
      answer = sum;
    }
  }
  printf("Answer: %d\n", answer);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
