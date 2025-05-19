#include <stdbool.h>
#include <stdio.h>
#define MAX_Y 3
#define MAX_X 3
#define BOARD (brd[MAX_Y][MAX_X])
typedef struct board {
  bool lock;
  int id; // 0: empty; 5: X; 2: O
} Board;
int newBoard(Board BOARD);
int printBoard(Board BOARD);
int checkPosition(int pos[2]);
int checkWin(Board BOARD);
int setid(Board BOARD, int pos[2], int id);
int getid(Board BOARD, int col, int lin);
int insert(Board BOARD, int ox, int pos[2]);
int initGame();

int main() {
  initGame();
  return 0;
}
int setid(Board BOARD, int pos[2], int id) {
  brd[pos[0]][pos[1]].id = id;
  brd[pos[0]][pos[1]].lock = true;
  return 0;
}
int getid(Board BOARD, int col, int lin) { return brd[lin][col].id; }

int newBoard(Board BOARD) {
  int i, j;
  for (i = 0; i < MAX_Y; i++) {
    for (j = 0; j < MAX_X; j++) {
      brd[i][j].id = 0;
      brd[i][j].lock = false;
    }
  }
  return 0;
}

int printBoard(Board BOARD) {
  int i, j;
  for (i = 0; i < MAX_Y; i++) {
    for (j = 0; j < MAX_X; j++) {
      printf("%2d", brd[i][j].id);
    }
    printf("\n");
  }
  return 0;
}

int checkPosition(int pos[2]) {
  if (pos[0] >= MAX_Y || pos[0] < 0) {
    return 1;
  } else if (pos[1] >= MAX_X || pos[1] < 0) {
    return 1;
  }
  return 0;
}
int checkWin(Board BOARD) {
  int i;
  // diagonais
  if (getid(brd, 0, 0) + getid(brd, 1, 1) + getid(brd, 2, 2) == 6) {
    printf("O wins");
    return 1;
  } else if (getid(brd, 0, 0) + getid(brd, 1, 1) + getid(brd, 2, 2) == 15) {
    printf("X wins");
    return 1;
  } else if (getid(brd, 2, 0) + getid(brd, 1, 1) + getid(brd, 0, 2) == 15) {
    printf("X wins");
  } else if (getid(brd, 2, 0) + getid(brd, 1, 1) + getid(brd, 0, 2) == 6) {
    printf("O wins");
  }
  for (i = 0; i < 3; i++) {
    // linhas
    if (getid(brd, i, 0) + getid(brd, i, 1) + getid(brd, i, 2) == 6) {
      printf("O wins");
      return 1;
    } else if (getid(brd, i, 0) + getid(brd, i, 1) + getid(brd, i, 2) == 15) {
      printf("X wins");
      return 1;
      // colunas
    } else if (getid(brd, 0, i) + getid(brd, 1, i) + getid(brd, 2, i) == 6) {
      printf("O wins");
      return 1;
    } else if (getid(brd, 0, i) + getid(brd, 1, i) + getid(brd, 2, i) == 15) {
      printf("X wins");
      return 1;
    }
  }

  return 0;
}

int insert(Board BOARD, int ox, int pos[2]) {
  if (brd[pos[0]][pos[1]].lock == true || checkPosition(pos) == 1) {
    return 1;
  } else {
    if (ox == false) {
      setid(brd, pos, 5);
    } else {
      setid(brd, pos, 2);
    }
  }
  return 0;
}
int initGame() {
  Board board[MAX_Y][MAX_X];
  int play[2];
  int turn;
  newBoard(board);
  while (true) {
    if (turn == false) {
      printf("Vez do X\n");
    } else {
      printf("Vez do O\n");
    }
    printf("digite a linha:");
    scanf("%d", &play[0]);
    printf("digite a coluna:");
    scanf("%d", &play[1]);
    play[0] -= 1;
    play[1] -= 1;
    if (insert(board, turn, play) == 1) {
      printf("[ERRO!]Posição Invalida - Tente Novamente\n");
    } else {
      if (checkWin(board) == 1)
        break;
      turn = !turn;
    }
    printBoard(board);
  }

  return 0;
}
