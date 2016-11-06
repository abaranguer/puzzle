#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

int main(int argc, char *argv[]) {
  int num;
  int i;
  char *line;

  for(i = 0; i < 1; i++) {
    num = random() % 10;
    printf("[%d] num=%d\n", i, num);

    line = readline("\n(1-9) or q (quit)? ");
    printf("char: %s\n", line);
    free(line); 
  }

  char s0[] = "123456\0";
  char s1[] = "5675";
  char s2[] = "123456";
  printf("s0: %s\n", s0);
  printf("s1: %s\n", s1);
  printf("s2: %s\n", s2);
  printf("s0 == s2? %s\n", strcmp(s0, s2) == 0 ? "equals" : "diff");

  return 0;
}
