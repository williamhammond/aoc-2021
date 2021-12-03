#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
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
  char line[MAX_LINE_LENGTH] = {0};
  unsigned int line_count = 0;

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  int zeroFrequencies[BIT_WIDTH] = {0, 0, 0, 0, 0};
  int oneFrequencies[BIT_WIDTH] = {0, 0, 0, 0, 0};
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    for (int i = 0; i < strlen(line); i++) {
      if (line[i] == '0') {
        zeroFrequencies[i] += 1;
      } else {
        oneFrequencies[i] += 1;
      }
    }
  }

  char gamma[BIT_WIDTH];
  char epsilon[BIT_WIDTH];
  for (int i = 0; i < BIT_WIDTH; i++) {
    if (zeroFrequencies[i] > oneFrequencies[i]) {
      gamma[i] = '0';
      epsilon[i] = '1';
    } else {
      gamma[i] = '1';
      epsilon[i] = '0';
    }
  }
  printf("gamma: %ld\n", bitsToDecimal(gamma));
  printf("epislon: %ld\n", bitsToDecimal(epsilon));

  printf("Result: %ld", bitsToDecimal(gamma) * bitsToDecimal(epsilon));
  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  free(line);
  return EXIT_SUCCESS;
}