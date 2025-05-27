#include <stdbool.h>
#include <stdio.h>
#define ERROR_MSG "\e[0;31mERRO\e[0m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BWHT "\e[1;37m"
#define COLOR_RESET "\e[0m"
#define MAX_Y 3
#define MAX_X 3
#define BOARD (brd[MAX_Y][MAX_X])
typedef struct board {
  bool lock;
  int id; // 0: empty; 5: X; 2: O
} Board;

char charX;
char charO;
char charE = '#';

int getid(Board BOARD, int col, int lin);
int setid(Board BOARD, int pos[2], int id);
int fd_zero(Board BOARD);
int newBoard(Board BOARD);
int printBoard(Board BOARD);
int checkPosition(int pos[2]);
int checkWin(Board BOARD);
int insert(Board BOARD, bool ox, int pos[2]);
int initGame();

int main() {
  printf("---------------------\n");
  printf(GRN "    Jogo da Velha    \n" COLOR_RESET);
  printf("---------------------\n");
  initGame();
  return 0;
}
int setid(Board BOARD, int pos[2], int id) {
  brd[pos[0]][pos[1]].id = id;
  brd[pos[0]][pos[1]].lock = true;
  return 0;
}
int getid(Board BOARD, int col, int lin) { return brd[lin][col].id; }
int fd_zero(Board BOARD) {
  int i, j;
  for (i = 0; i < MAX_Y; i++) {
    for (j = 0; j < MAX_X; j++) {
      if (brd[i][j].id == 0) {
        return 1;
      } else {
        continue;
      }
    }
  }
  return 0;
}
int getskins() {
  printf("Digite uma letra para representar o " BWHT "Jogador 1: " COLOR_RESET);
  scanf("%s", &charX);
  printf("Digite uma letra para representar o " BWHT "Jogador 2: " COLOR_RESET);
  scanf("%s", &charO);
  if ((charO == charE) || (charX == charE) || (charO == charX)) {
    return 1;
  }
  return 0;
}
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
  printf("-------\n");
  for (i = 0; i < MAX_Y; i++) {
    for (j = 0; j < MAX_X; j++) {
      if (brd[i][j].id != 0)
        printf("%2c", brd[i][j].id == 5 ? charX : charO);
      else
        printf("%2c", '#');
    }
    printf("\n");
  }
  printf("-------\n");
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
    return 1;
  } else if (getid(brd, 0, 0) + getid(brd, 1, 1) + getid(brd, 2, 2) == 15) {
    return 2;
  } else if (getid(brd, 2, 0) + getid(brd, 1, 1) + getid(brd, 0, 2) == 15) {
    return 2;
  } else if (getid(brd, 2, 0) + getid(brd, 1, 1) + getid(brd, 0, 2) == 6) {
    return 1;
  }
  for (i = 0; i < 3; i++) {
    // linhas
    if (getid(brd, i, 0) + getid(brd, i, 1) + getid(brd, i, 2) == 6) {
      return 1;
    } else if (getid(brd, i, 0) + getid(brd, i, 1) + getid(brd, i, 2) == 15) {
      return 2;
      // colunas
    } else if (getid(brd, 0, i) + getid(brd, 1, i) + getid(brd, 2, i) == 6) {
      return 1;
    } else if (getid(brd, 0, i) + getid(brd, 1, i) + getid(brd, 2, i) == 15) {
      return 2;
    }
  }
  if (fd_zero(brd) == 0) {
    return 3;
  }
  return 0;
}

int insert(Board BOARD, bool ox, int pos[2]) {
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
  bool check = true;
  while (getskins() == 1) {
    printf("[" ERROR_MSG "]"
           "Letra Inválida - Tente Novamente\n");
  }
  newBoard(board);
  while (check) {
    if (turn) {
      printf("Vez do %c\n", charO);
    } else {
      printf("Vez do %c\n", charX);
    }
    printf("digite a linha:");
    scanf("%d", &play[0]);
    printf("digite a coluna:");
    scanf("%d", &play[1]);
    play[0] -= 1;
    play[1] -= 1;
    if (insert(board, turn, play) == 1) {
      printf("[" ERROR_MSG "]"
             "Posição Inválida - Tente Novamente\n");
    } else {
      switch (checkWin(board)) {
      case 1:
        printf("%c wins!\n", charO);
        check = false;
        break;
      case 2:
        printf("%c wins!\n", charX);
        check = false;
        break;
      case 3:
        printf("Draw\n");
        check = false;
        break;
      default:
        break;
      }
      turn = !turn;
    }
    printBoard(board);
  }

  return 0;
}
