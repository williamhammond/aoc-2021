#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

int main(int argc, char** argv) {
  char* path = "input.txt";
  char line[MAX_LINE_LENGTH] = {0};

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  int bottom = -1;
  int middle = -1;
  int top = -1;

  int previousSum = -1;
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
    if ((top != -1) && (middle != -1) && (bottom != -1)) {
      currentSum = bottom + middle + top;
      if ((previousSum != -1) && currentSum > previousSum) {
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