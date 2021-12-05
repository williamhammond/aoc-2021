
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define VENT_COUNT 500

typedef struct point {
  int x;
  int y;
} point;

typedef struct line {
  point start;
  point end;
} line;

int main(int argc, char** argv) {
  char* path = "input.txt";
  char line[MAX_LINE_LENGTH] = {0};
  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  struct line vents[VENT_COUNT];
  int ventCount = 0;
  int maxX = 0;
  int maxY = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    int x1, y1, x2, y2 = 0;
    int read = sscanf(line, "%d,%d -> %d,%d", &x1, &y1, &x2, &y2);
    if (read != 4) {
      // printf("Read %d from line", read);
      return EXIT_FAILURE;
    }
    if (maxX < x1) {
      maxX = x1;
    }

    if (maxX < x2) {
      maxX = x2;
    }

    if (maxY < y1) {
      maxY = y1;
    }

    if (maxY < y2) {
      maxY = y2;
    }

    struct point start;
    start.x = x1;
    start.y = y1;

    struct point end;
    end.x = x2;
    end.y = y2;

    struct line vent;
    vent.start = start;
    vent.end = end;
    vents[ventCount] = vent;

    ventCount++;
  }

  int grid[1024][1024] = {};
  int dangerousTiles = 0;

  for (int ventIdx = 0; ventIdx < ventCount; ventIdx++) {
    if (vents[ventIdx].start.x == vents[ventIdx].end.x) {
      // printLine(vents[ventIdx]);
      int lower = (vents[ventIdx].start.y < vents[ventIdx].end.y)
                      ? vents[ventIdx].start.y
                      : vents[ventIdx].end.y;
      int upper = (vents[ventIdx].start.y > vents[ventIdx].end.y)
                      ? vents[ventIdx].start.y
                      : vents[ventIdx].end.y;
      for (int i = lower; i <= upper; i++) {
        // printf("Increasing x=%d y=%d from %d to %d\n", vents[ventIdx].start.x,
        //        i, grid[vents[ventIdx].start.x][i],
        //        grid[vents[ventIdx].start.x][i] + 1);
        grid[vents[ventIdx].start.x][i]++;
      }
      // printGrid(grid, maxX, maxY);

    } else if (vents[ventIdx].start.y == vents[ventIdx].end.y) {
      // printLine(vents[ventIdx]);
      int lower = (vents[ventIdx].start.x < vents[ventIdx].end.x)
                      ? vents[ventIdx].start.x
                      : vents[ventIdx].end.x;
      int upper = (vents[ventIdx].start.x > vents[ventIdx].end.x)
                      ? vents[ventIdx].start.x
                      : vents[ventIdx].end.x;
      for (int i = lower; i <= upper; i++) {
        // printf("Increasing x=%d y=%d from %d to %d\n", i,
        //        vents[ventIdx].start.y, grid[i][vents[ventIdx].start.y],
        //        grid[i][vents[ventIdx].start.y] + 1);
        grid[i][vents[ventIdx].start.y]++;
      }
      // printGrid(grid, maxX, maxY);
    }
  }

  for (int i = 0; i <= maxX; i++) {
    for (int j = 0; j <= maxY; j++) {
      if (grid[i][j] > 1) {
        dangerousTiles++;
      }
    }
  }
  printf("Number of dangerous tiles is %d\n", dangerousTiles);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  free(line);
  printf("Program exited sucessfully");
  return EXIT_SUCCESS;
}

void printLine(line line) {
  printf("(%d, %d) -> (%d, %d)\n", line.start.x, line.start.y, line.end.x,
         line.end.y);
}

void printPoint(point point) { printf("(%d, %d)", point.x, point.y); }

void printGrid(int grid[512][512], int maxX, int maxY) {
  puts("");
  for (int i = 0; i <= maxX; i++) {
    for (int j = 0; j <= maxY; j++) {
      printf("%d ", grid[i][j]);
    }
    puts("");
  }
  puts("");
}