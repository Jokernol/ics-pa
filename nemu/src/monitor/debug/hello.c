#include <stdio.h>

int main() {
  FILE* fp = fopen("input.txt", "r");
  char str[256] = {'\0'};

  while(fgets(str, 256, fp) != NULL) {
    puts(str);
  }

  fclose(fp);
}