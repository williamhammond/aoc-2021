#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char** argv) {
  char* path = "input.txt";
  char line[MAX_LINE_LENGTH] = {0};
  unsigned int line_count = 0;

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  int bottom = NULL;
  int middle = NULL;
  int top = NULL;

  int previousSum = NULL;
  int currentSum = 0;
  int result = 0;

  int counter = 1;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    int current = atoi(line);
    switch (counter % 3) {
      case 0:
        top = current;
        break;
      case 1:
        bottom = current;
        break;
      case 2:
        middle = current;
        break;
      default:
        break;
    }
    if (top && middle && bottom) {
      currentSum = bottom + middle + top;
      if (previousSum && currentSum > previousSum) {
        result++;
      }
      previousSum = currentSum;
    }
    counter++;
  }

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  printf("result :%d", result);
  return EXIT_SUCCESS;
}