#ifndef PUZZLE
#define PUZZLE
#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
/*
 * puzzle de 3x3
 * puzzle resolt    puzzle desordenat
 * +---+            +---+
 * |123|            |038|
 * |456|            |245|
 * |780|            |761|
 * +---+            +---+
 * Ordena el puzzle movent els números.
 * Indica quin número vols moure a l'espai en blanc adjacent
 * El programa ha de
 * 1. generar un puzzle desordenat
 * 2. mostrar el puzzle
 * 3. demanar quin número es vol moure
 * 4. veure si es pot moure 
 * 5.  si no es pot moure, dir-ho i tornar al punt 2
 * 6.  si es pot moure, fer el moviment.
 * 7.    comprovar si ha guanyat
 * 8.      si ha guanyat acabar eljoc
 * 9.      si no ha guanyat, tornar al punt 2.
 */

int puzzle[] = {10,10,10,10,10,10,10,10,10};

typedef struct POS {
  int row;
  int column;
} T_POS;

int randint(int range) {
  return random() % (range + 1);  
}

void genera_puzzle(int puzzle[]) {
  int i;
  int j;
  int repeat;
  for(i = 0; i < 9; i++) {
    repeat = 1;
    while (repeat) {
      j = randint(8);
      if (puzzle[j] == 10) {
        puzzle[j] = i;
        repeat = 0;
      }
    }
  }
}

void mostra_puzzle(int puzzle[]) {
  printf("+---+\n");
  printf("|%d%d%d|\n", puzzle[0], puzzle[1], puzzle[2]);
  printf("|%d%d%d|\n", puzzle[3], puzzle[4], puzzle[5]);
  printf("|%d%d%d|\n", puzzle[6], puzzle[7], puzzle[8]);
  printf("+---+\n");
  printf("\n");
}

int demanar_numero() {
  int valid = FALSE;
  char *line;
  char c;

  while(!valid) {
    line = readline("(1-9) or q (quit)? ");
    if (strlen(line) == 1) {
      if ((strcmp(line, "q") == 0) || (strcmp(line, "Q") == 0)) {
	  valid = TRUE;
          free(line);
          printf("\nGame interrupted\n");
          exit(0);
      }
  	
      c = line[0];
      free(line);

      if ((c == '0') || (c == '1') || (c == '2') ||
          (c == '3') || (c == '4') || (c == '5') ||
          (c == '6') || (c == '7') || (c == '8')) {
        valid = TRUE;      
      }       
    }
  }
  
  return (c - '0');
}


T_POS obtenir_posicio(int num, int puzzle[]) { 
  T_POS pos;
  int row;
  int column;

  for(row = 0; row < 3; row++) {
    for(column = 0; column < 3; column++) {
      if (num == puzzle[row * 3 + column]) {
        pos.row = row;
        pos.column = column;
        break;
      }
    }
  }

  return(pos);
}     

int verifica_numero(int num, int puzzle[]) {
  int valid;
  T_POS pos;

  pos = obtenir_posicio(num, puzzle);
  valid = verifica_posicio(pos, puzzle);

  return valid;
}

int verifica_posicio(T_POS pos, int puzzle[]) {
  int valid = FALSE;
  int row = pos.row;
  int column = pos.column;

  if ((row - 1) >= 0) {
    if (puzzle[(row - 1) * 3 + column] == 0) {
      valid = TRUE;  
    }
  }

  if ((row + 1) <= 2) {
    if (puzzle[(row + 1) * 3 + column] == 0) {
      valid = TRUE;
    }
  }

  if ((column - 1) >= 0) {
    if (puzzle[(row * 3) + (column - 1)] == 0) {
      valid = TRUE;
    }
  }

  if ((column + 1) <= 2) {
    if (puzzle[(row * 3) + (column + 1)] == 0) {
      valid = TRUE;
    }
  }

  return valid;
}

void moviment(int num, int puzzle[]) {
  T_POS pos;
  pos = obtenir_posicio(num, puzzle);

  int row = pos.row;
  int column = pos.column;
  
  if ((row - 1) >= 0) {
    if (puzzle[(row - 1) * 3 + column] == 0) {
      puzzle[(row - 1) * 3 + column] = num;
      puzzle[(row * 3) + column] = 0;
    }
  }

  if ((row + 1) <= 2) {
    if (puzzle[(row + 1) * 3 + column] == 0) {
      puzzle[(row + 1) * 3 + column] = num;
      puzzle[(row * 3) + column] = 0;
    }
  }
  if ((column - 1) >= 0) {
    if (puzzle[(row * 3) + (column - 1)] == 0) {
      puzzle[(row * 3) + (column - 1)] = num;
      puzzle[(row * 3) + column] = 0;
    }
  }

  if ((column + 1) <= 2) {
    if (puzzle[(row * 3) + (column + 1)] == 0) {
      puzzle[(row * 3) + (column + 1)] = num;
      puzzle[(row * 3) + column] = 0;
    }
  }
}

int es_puzzle_completat(int puzzle[]) {
  char solved[]="123456780";
  char actual[10];
  int i;
 
  for(i = 0; i < 9; i++) {
    actual[i] = puzzle[i] + '0';
  }
  actual[9] = 0;

  if (strcmp(solved, actual) == 0) {
    return TRUE;
  } else {
    return FALSE;
  }
}

int main(int argc, char *argv[]) {
  int final = 0;
  int num;
  genera_puzzle(puzzle);
  while(!final) {
    final = 0;
    mostra_puzzle(puzzle);
    num = demanar_numero();
    if (verifica_numero(num, puzzle)) {
      moviment(num, puzzle);
      if (es_puzzle_completat(puzzle)) {
        printf("\nWell done!!\n");
        mostra_puzzle(puzzle);
        final = 1;
      }
    }
  }
}

#endif
