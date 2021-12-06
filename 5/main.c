
#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define VENT_COUNT 500

enum DIRECTION {
  NORTH,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST
};

typedef struct point {
  int x;
  int y;
} point;

typedef struct line {
  point start;
  point end;
} line;

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

int orientation(point start, point end) {
  if ((start.x > end.x) && (start.y == end.y)) {
    return NORTH;
  }

  if ((start.x < end.x) && (start.y > end.y)) {
    return NORTH_EAST;
  }

  if ((start.x == end.x) && (start.y < end.y)) {
    return EAST;
  }

  if ((start.x < end.x) && (start.y < end.y)) {
    return SOUTH_EAST;
  }

  if ((start.x < end.x) && (start.y == end.y)) {
    return SOUTH;
  }

  if ((start.x > end.x) && (start.y < end.y)) {
    return SOUTH_WEST;
  }

  if ((start.x == end.x) && (start.y > end.y)) {
    return WEST;
  }

  if ((start.x > end.x) && (start.y > end.y)) {
    return NORTH_WEST;
  }

  return -1;
}

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
      printf("Read %d from line", read);
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

  int grid[1024][1024] = {0};
  int dangerousTiles = 0;

  for (int ventIdx = 0; ventIdx < ventCount; ventIdx++) {
    struct line vent = vents[ventIdx];
    struct point start = vent.start;
    struct point end = vent.end;

    struct point current = start;

    switch (orientation(start, end)) {
      case NORTH:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x--;
        }
        break;

      case NORTH_EAST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x++;
          current.y--;
        }
        break;

      case EAST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.y++;
        }
        break;

      case SOUTH_EAST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x++;
          current.y++;
        }
        break;

      case SOUTH:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x++;
        }
        break;

      case SOUTH_WEST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x--;
          current.y++;
        }
        break;

      case WEST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.y--;
        }
        break;

      case NORTH_WEST:
        while ((current.x != end.x) || (current.y != end.y)) {
          grid[current.x][current.y]++;
          current.x--;
          current.y--;
        }
        break;
      default:
        printf("Bad orientation for:\n");
        printLine(vent);
        return EXIT_FAILURE;
    }
    grid[end.x][end.y]++;
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
  printf("Program exited sucessfully");
  return EXIT_SUCCESS;
}