#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static char* p;

static uint8_t choose(uint8_t n) {
  return rand() % n;
}

static void gen_num() {
  char str[16];
  
  sprintf(str, "%u", rand() % 100);

  uint32_t len = strlen(str);
  
  strncpy(p, str, len);

  p += len;
}

static void gen(char c) {
  *p = c;

  p ++;
}

static void gen_rand_op() {
  switch (choose(4)) {
    case 0: *p = '+'; break;
    case 1: *p = '-'; break;
    case 2: *p = '*'; break;
    case 3: *p = '/'; break;
  }

  p ++;
}

static uint8_t op_num;

static inline void gen_rand_expr() {
  switch (choose(3)) {
    case 0: 
      if (op_num == 0) {
        gen_rand_expr();
      } else {
        gen_num();
      }

      break;
    case 1: 
      gen('(');
      gen_rand_expr();
      gen(')');
      break;
    default:
      op_num++;

      if ((p - buf) > 24) {
        gen_num();
      } else {
        gen_rand_expr();
        gen_rand_op();
        gen_rand_expr();
      }

      break;
  }
}

int main(int argc, char *argv[]) {
  int seed = time(0);
  srand(seed);

  int loop = 1;
  if (argc > 1) {
    sscanf(argv[1], "%d", &loop);
  }
  int i;
  for (i = 0; i < loop; i ++) {
    p = buf;
    op_num = 0;
    
    memset(buf, '\0', sizeof(buf));
    memset(code_buf, '\0', sizeof(code_buf));
    
    gen_rand_expr();

    sprintf(code_buf, code_format, buf);

    FILE *fp = fopen("/tmp/.code.c", "w");
    assert(fp != NULL);
    fputs(code_buf, fp);
    fclose(fp);

    int ret = system("gcc /tmp/.code.c -o /tmp/.expr");
    if (ret != 0) continue;

    fp = popen("/tmp/.expr", "r");
    assert(fp != NULL);

    int result;
    fscanf(fp, "%d", &result);
    pclose(fp);

    printf("%u %s\n", result, buf);
  }

  return 0;
}
