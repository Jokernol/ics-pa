#include <stdio.h>
#include <isa.h>
#include <stdlib.h>

void init_monitor(int, char *[]);
void engine_start();
int is_exit_status_bad();

word_t expr(char *e, bool *success);

static int file_gets() {
  FILE* fp = fopen("/home/jokernol/Anything/ics-pa/nemu/tools/gen-expr/input", "r");
  char str[256] = {'\0'};

  if(fp == NULL) {
    perror("");
    return -1;
  }
  
  while(fgets(str, 256, fp) != NULL) {
    char *ans = strtok(str, " ");
    char *exp = ans + strlen(ans) + 1;
    puts("s");
    bool success = true;

    if (expr(exp, &success) == atoi(ans)) {
      printf("%s %s %s\n", ans, exp, "True");
    } else {
      printf("%s %s %s\n", ans, exp, "False");
    }
  }

  fclose(fp);

  return 0;
}

int main(int argc, char *argv[]) {
  /* Initialize the monitor. */
  //init_monitor(argc, argv);

  /* Start engine. */
  //engine_start();

  //return is_exit_status_bad();
  file_gets();

  return 0;
}


