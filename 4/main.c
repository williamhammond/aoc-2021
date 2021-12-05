#if WIN32
#define _CRT_SECURE_NO_DEPRECATE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define BINGO_SIZE 5
#define BOARD_COUNT 100

#define TRUE 1
#define FALSE 0

int main(int argc, char** argv) {
  char* path = "input.txt";

  FILE* file = fopen(path, "r");

  if (!file) {
    perror(path);
    return EXIT_FAILURE;
  }

  char line[MAX_LINE_LENGTH] = {0};
  int moves[MAX_LINE_LENGTH];
  int moveCount = 0;
  if (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    char* token = strtok(line, ",");
    while (token) {
      int move = atoi(token);
      moves[moveCount] = move;
      moveCount++;
      token = strtok(NULL, ",");
    }
  }
  // Eat leading newline
  fgets(line, MAX_LINE_LENGTH, file);

  int boards[BOARD_COUNT][BINGO_SIZE][BINGO_SIZE] = {};
  int boardCount = 0;
  int rowCount = 0;
  while (fgets(line, MAX_LINE_LENGTH, file)) {
    line[strcspn(line, "\n")] = 0;
    if (!line[0]) {
      boardCount++;
      rowCount = 0;
      continue;
    }

    int a, b, c, d, e;
    sscanf(line, "%d%d%d%d%d", &a, &b, &c, &d, &e);

    boards[boardCount][rowCount][0] = a;
    boards[boardCount][rowCount][1] = b;
    boards[boardCount][rowCount][2] = c;
    boards[boardCount][rowCount][3] = d;
    boards[boardCount][rowCount][4] = e;
    rowCount++;
  }

  int winningBoard = -1;
  int lastMove = -1;
  for (int j = 0; j < moveCount; j++) {
    int move = moves[j];
    for (int row = 0; row < BINGO_SIZE; row++) {
      for (int col = 0; col < BINGO_SIZE; col++) {
        for (int boardIdx = 0; boardIdx < BOARD_COUNT; boardIdx++) {
          if (boards[boardIdx][row][col] == move) {
            // printf("Move %d matched board %d row=%d col=%d with value %d\n",
            //        move, boardIdx, row, col, boards[boardIdx][row][col]);
            boards[boardIdx][row][col] = -1;
            // printBoard(boards[boardIdx]);
            if (isWinner(boards[boardIdx]) == TRUE) {
              winningBoard = boardIdx;
              lastMove = move;
              goto winner;
            }
          }
        }
      }
    }
  }

winner:
  printf("Board %d is the winner with score %d\n\n", winningBoard,
         getScore(boards[winningBoard], lastMove));
  printBoard(boards[winningBoard]);

  if (fclose(file)) {
    return EXIT_FAILURE;
    perror(path);
  }
  return EXIT_SUCCESS;
}

void printBoard(int board[BINGO_SIZE][BINGO_SIZE]) {
  puts("");
  for (int i = 0; i < BINGO_SIZE; i++) {
    for (int j = 0; j < BINGO_SIZE; j++) {
      printf("%d ", board[i][j]);
    }
    puts("");
  }
  puts("");
}

int isRowWin(int board[BINGO_SIZE][BINGO_SIZE]) {
  for (int i = 0; i < BINGO_SIZE; i++) {
    int isWin = TRUE;
    for (int j = 0; j < BINGO_SIZE; j++) {
      if (board[i][j] != -1) {
        isWin = FALSE;
      }
    }
    if (isWin) {
      return TRUE;
    }
  }
  return FALSE;
}

int isColWin(int board[BINGO_SIZE][BINGO_SIZE]) {
  for (int i = 0; i < BINGO_SIZE; i++) {
    int isWin = TRUE;
    for (int j = 0; j < BINGO_SIZE; j++) {
      if (board[j][i] != -1) {
        isWin = FALSE;
      }
    }
    if (isWin) {
      return TRUE;
    }
  }
  return FALSE;
}

int isWinner(int board[BINGO_SIZE][BINGO_SIZE]) {
  return isColWin(board) || isRowWin(board);
}

int getScore(int board[BINGO_SIZE][BINGO_SIZE], int move) {
  int sum = 0;
  for (int i = 0; i < BINGO_SIZE; i++) {
    for (int j = 0; j < BINGO_SIZE; j++) {
      if (board[i][j] != -1) {
        sum += board[i][j];
      }
    }
  }
  printf("%d * %d = %d\n", sum, move, sum * move);

  return sum * move;
}