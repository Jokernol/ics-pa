#include <stdio.h>

void init_monitor(int, char *[]);
void engine_start();
int is_exit_status_bad();

int main(int argc, char *argv[]) {
  FILE* fp = fopen("input.txt", "r");
  char str[256] = {'\0'};

  if(fp == NULL) {
    perror("打开文件时发生错误");
    return -1;
  }

  while(fgets(str, 256, fp) != NULL) {
    puts(str);
  }

  fclose(fp);
  /* Initialize the monitor. */
  //init_monitor(argc, argv);
  
  /* Start engine. */
  //engine_start();

  return 0;
  //return is_exit_status_bad();
}
