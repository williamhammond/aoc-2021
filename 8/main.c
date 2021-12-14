
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 8192
#define SIZE 200

int main(int argc, char** argv) {
  char* path = "input.txt";

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  // char** strings = malloc(SIZE * sizeof(char*));
  int count = 0;

  char line[MAX_LINE_LENGTH] = {0};
  while(fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    char* wires = strtok(line, "|");
    char* output = strtok(NULL, "|");

    char* token = strtok(wires, " ");
    while (token != NULL) {
      printf("%s ", token);
      token = strtok(NULL, " ");
    }
    puts("\n");

    token = strtok(output, " ");
    while (token != NULL) {
      printf("%s ", token);
      if (strlen(token) == 2 || strlen(token) == 3 || strlen(token) == 4 ||
          strlen(token) == 7) {  // NOLINT
        count++;
      }
      token = strtok(NULL, " ");
    }
    printf("\n");
  }

  printf("Result: %d\n", count);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}
