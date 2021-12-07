
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

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};
  if (fgets(line, MAX_LINE_LENGTH, file)) {
  }

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
