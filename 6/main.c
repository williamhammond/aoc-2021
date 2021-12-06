#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define BIRTH_TIMER 6
#define NEW_FISH_TIMER 8
#define DAYS 256

int main(int argc, char** argv) {
  char* path = "input.txt";

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};
  long long fishCounts[NEW_FISH_TIMER + 1] = {0};
  if (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    char* token = strtok(line, ",");
    while (token) {
      int fish = atoi(token);
      fishCounts[fish]++;
      token = strtok(NULL, ",");
    }
  }
  printf("Day 0: ");
  for (int i = 0; i <= NEW_FISH_TIMER; i++) {
    printf("%d=%lld ", i, fishCounts[i]);
  }
  printf("\n");

  for (int day = 1; day <= DAYS; day++) {
    long long justSpawned = fishCounts[0];             // NOLINT
    fishCounts[0] = fishCounts[1];               // NOLINT
    fishCounts[1] = fishCounts[2];               // NOLINT
    fishCounts[2] = fishCounts[3];               // NOLINT
    fishCounts[3] = fishCounts[4];               // NOLINT
    fishCounts[4] = fishCounts[5];               // NOLINT
    fishCounts[5] = fishCounts[6];               // NOLINT
    fishCounts[6] = fishCounts[7];               // NOLINT
    fishCounts[7] = fishCounts[NEW_FISH_TIMER];  // NOLINT
    fishCounts[NEW_FISH_TIMER] = justSpawned;
    fishCounts[BIRTH_TIMER] += justSpawned;
  }
  long long sum = 0;
  for (int i = 0; i < NEW_FISH_TIMER + 1; i++) {
    sum += fishCounts[i];
  }
  printf("There were %lld fish after %d days", sum, DAYS);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
