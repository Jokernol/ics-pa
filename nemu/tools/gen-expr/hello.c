#include <stdio.h>

int main() {
  FILE* fp = fopen("/home/jokernol/Anything/ics-pa/nemu/tools/gen-expr/input", "r");
  char str[256] = {'\0'};

  if(fp == NULL) {
    perror("");
    return -1;
  }

  while(fgets(str, 256, fp) != NULL) {
    puts(str);
  }

  fclose(fp);

  return 0;
}