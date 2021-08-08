#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

// this should be enough
static char buf[65536] = {};
static char hex_buf[65536] = {};
static char code_buf[65536 + 128] = {}; // a little larger than `buf`
static char *code_format =
"#include <stdio.h>\n"
"int main() { "
"  unsigned char x = 0;"
"  unsigned result = %s; "
"  printf(\"%%u\", result); "
"  return 0; "
"}";

static char* p;
static char* q;

static uint8_t choose(uint8_t n) {
  return rand() % n;
}

static void gen_num() {
  char str[16];
  char hex_str[16];
  
  uint16_t num = rand() % 100;

  sprintf(str, "%u", num);
  sprintf(hex_str, "0x%X", num);

  uint32_t len = strlen(str);
  uint32_t hex_len = strlen(hex_str);

  strncpy(p, str, len);
  strncpy(q, hex_str, hex_len);

  p += len;
  q += hex_len;
}

static void gen(char c) {
  *p = c;
  *q = c;

  p ++;
  q ++;
}

static void gen_rand_op() {
  switch (choose(4)) {
    case 0: 
      *p = '+';
      *q = '+';
      break;
    case 1: 
      *p = '-';
      *q = '-';
      break;
    case 2:
      *p = '*';
      *q = '*';
      break;
    case 3:
      *p = '/';
      *q = '/';
      break;
  }

  p ++;
  q ++;
}

static uint8_t op_num;

static inline void gen_rand_expr() {
  switch (choose(3)) {
    case 0: 
      if (op_num == 0) {
        gen_rand_expr();
      } else {
        gen_num();
        gen(' ');
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
        gen(' ');
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
    q = hex_buf;
    op_num = 0;
    
    memset(buf, '\0', sizeof(buf));
    memset(hex_buf, '\0', sizeof(hex_buf));
    memset(code_buf, '\0', sizeof(code_buf));
    
    gen_rand_expr();

    sprintf(code_buf, code_format, hex_buf);

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
