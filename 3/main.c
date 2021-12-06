#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BIT_STRINGS 1000
#define BIT_WIDTH 12

long bitsToDecimal(const char* str) {
  long val = 0;
  for (int i = 0; i < BIT_WIDTH; i++) {
    if (str[i] == '1') {
      val += (int)pow(2, BIT_WIDTH - i - 1);
    }
  }
  return val;
}

int main(int argc, char** argv) {
  char* path = "input.txt";
  char line[BIT_WIDTH] = {0};

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char reports[MAX_BIT_STRINGS][BIT_WIDTH + 1];
  int reportCount = 0;
  while (fgets(line, BIT_WIDTH * 2, file)) {
    line[strcspn(line, "\n")] = 0;
    strncpy(reports[reportCount], line, BIT_WIDTH + 1);
    reportCount++;
  }

  char zeroBuffer[MAX_BIT_STRINGS][BIT_WIDTH + 1];
  char oneBuffer[MAX_BIT_STRINGS][BIT_WIDTH + 1];
  for (int bitIdx = 0; bitIdx < BIT_WIDTH; bitIdx++) {
    int zeroCount = 0;
    int oneCount = 0;

    for (int reportIdx = 0; reportIdx < reportCount; reportIdx++) {
      char* report = reports[reportIdx];
      if (report[bitIdx] == '0') {
        strncpy(zeroBuffer[zeroCount], report, BIT_WIDTH + 1);
        zeroCount++;
      } else {
        strncpy(oneBuffer[oneCount], report, BIT_WIDTH + 1);
        oneCount++;
      }
    }

    if (zeroCount > oneCount) {
      reportCount = zeroCount;
      for (int i = 0; i < reportCount; i++) {
        strncpy(reports[i], zeroBuffer[i], BIT_WIDTH + 1);
      }
    } else {
      reportCount = oneCount;
      for (int i = 0; i < reportCount; i++) {
        strncpy(reports[i], oneBuffer[i], BIT_WIDTH + 1);
      }
    }
    if (bitIdx == (BIT_WIDTH - 1)) {
      printf("Oxygen result %s\n", reports[0]);
    }
  }

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }

  puts("Program completed successfully");
  return EXIT_SUCCESS;
}