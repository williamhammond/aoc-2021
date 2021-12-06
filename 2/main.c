
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef enum { UP, DOWN, FORWARD } move;

move parseMove(char* move) {
  if (strcmp(move, "down") == 0) {
    return DOWN;
  }

  if (strcmp(move, "up") == 0) {
    return UP;
  }

  if (strcmp(move, "forward") == 0) {
    return FORWARD;
  }
  printf("move %s is not valid!", move);
  exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
  char* path = "input.txt";
  char line[MAX_LINE_LENGTH] = {0};

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  int x = 0;
  int y = 0;
  int aim = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    char* token = strtok(line, " ");
    move move = parseMove(token);
    token = strtok(NULL, " ");
    int magnitude = atoi(token);
    switch (move) {
      case UP:
        aim -= magnitude;
        break;
      case DOWN:
        aim += magnitude;
        break;
      case FORWARD:
        x += magnitude;
        y += aim * magnitude;
        break;
      default:
        printf("Invalid move %d!", move);
        return EXIT_FAILURE;
    }
  }

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  printf("x: %d, y: %d\n", x, y);
  return EXIT_SUCCESS;
}