#include <isa.h>
#include <stdlib.h>

/* We use the POSIX regex functions to process regular expressions.
 * Type 'man regex' for more information about POSIX regex functions.
 */
#include <regex.h>

enum {
  TK_NOTYPE = 256,
  TK_EQ,
  TK_OR,
  TK_AND,
  TK_NOT,
  TK_NUM,
  TK_NOTEQ,
  TK_HEXNUM,
  TK_REGISTER
  /* TODO: Add more token types */

};

static struct rule {
  char *regex;
  int token_type;
} rules[] = {

  /* TODO: Add more rules.
   * Pay attention to the precedence level of different rules.
   */

  {" +", TK_NOTYPE},    // spaces
  {"\\+", '+'},         // plus
  {"-", '-'},           // minus
  {"\\*", '*'},         // mult
  {"/", '/'},           // divide
  {"\\(", '('},
  {"\\)", ')'},
  {"\\|\\|", TK_OR},
  {"\\&\\&", TK_AND},
  {"!", TK_NOT},
  {"!=", TK_NOTEQ},
  {"\\b0[xX][0-9A-Fa-f]+\\b", TK_HEXNUM},
  {"\\b$\\w+\\b", TK_REGISTER},
  {"\\b[0-9]+\\b", TK_NUM},
  {"==", TK_EQ},        // equal
};

#define NR_REGEX (sizeof(rules) / sizeof(rules[0]) )

static regex_t re[NR_REGEX] = {};

/* Rules are used for many times.
 * Therefore we compile them only once before any usage.
 */
void init_regex() {
  int i;
  char error_msg[128];
  int ret;

  for (i = 0; i < NR_REGEX; i ++) {
    ret = regcomp(&re[i], rules[i].regex, REG_EXTENDED);
    if (ret != 0) {
      regerror(ret, &re[i], error_msg, 128);
      panic("regex compilation failed: %s\n%s", error_msg, rules[i].regex);
    }
  }
}

typedef struct token {
  int type;
  char str[32];
} Token;

static Token tokens[32] __attribute__((used)) = {};
static int nr_token __attribute__((used))  = 0;

static bool make_token(char *e) {
  int position = 0;
  int i;
  regmatch_t pmatch;

  nr_token = 0;

  while (e[position] != '\0') {
    /* Try all rules one by one. */
    for (i = 0; i < NR_REGEX; i ++) {
      if (regexec(&re[i], e + position, 1, &pmatch, 0) == 0 && pmatch.rm_so == 0) {
        char *substr_start = e + position;
        int substr_len = pmatch.rm_eo;

        Log("match rules[%d] = \"%s\" at position %d with len %d: %.*s",
            i, rules[i].regex, position, substr_len, substr_len, substr_start);

        position += substr_len;

        /* TODO: Now a new token is recognized with rules[i]. Add codes
         * to record the token in the array `tokens'. For certain types
         * of tokens, some extra actions should be performed.
         */

        switch (rules[i].token_type) {
          case TK_NOTYPE: 
            break;
          case TK_REGISTER:
          default:
            tokens[nr_token].type = rules[i].token_type;
            strncpy(tokens[nr_token].str, substr_start, substr_len);
            
            nr_token++;
            
            break;
        }

        break;
      }
    }

    if (i == NR_REGEX) {
      printf("no match at position %d\n%s\n%*.s^\n", position, e, position, "");
      return false;
    }
  }

  return true;
}

bool check_parentheses(Token *tokens, uint32_t left, uint32_t right, bool *success) {
  int8_t n;
  uint8_t i;

  bool flag = true;

  for (i = left, n = 0; i <= right; i ++) {
    if (i != left && n == 0) {
      flag = false;
    }

    if (tokens[i].type == '(') {
      n ++;
    } else if (tokens[i].type == ')') {
      n --;
    }
    
    if (n < 0) {
      *success = false;
      break;
    }
  }

  if (n != 0) {
    *success = false;
  }

  return (n == 0 && tokens[0].type == '(' && tokens[nr_token - 1].type == ')' && flag) ? true : false;
}

void search_main_op(Token *tokens, uint32_t left, uint32_t right, bool *success, uint32_t *op, uint8_t *op_type) {
  uint8_t i;
  bool flag = true;

  for (i = left; i <= right; i ++) {
    if (tokens[i].type == '(') {
      flag = false;
    } else if (tokens[i].type == ')') {
      flag = true;
    }

    if (flag && (tokens[i].type == '+' || tokens[i].type == '-' || tokens[i].type == '*' || tokens[i].type == '/')) {
      if (!*op_type) {
        *op = i;
        *op_type = tokens[i].type;
      }
      
      if ((*op_type == '*' || *op_type == '/') && (tokens[i].type == '*' || tokens[i].type == '/')) {
        *op = i;
        *op_type = tokens[i].type;
      }

      if (tokens[i].type == '+' || tokens[i].type == '-') {
        *op = i;
        *op_type = tokens[i].type;
      }
    }
  }

  if (!op && !op_type) {
    *success = false;
  }
}

word_t eval(Token *tokens, uint32_t left, uint32_t right, bool *success) {
  if (left > right || *success == false) {
    /* Bad expression */
    return 0;
  }else if (left == right) {
    /* Single token.
     * For now this token should be a number.
     * Return the value of the number.
     */
    return atoi(tokens[left].str);
  }else if (check_parentheses(tokens, left, right, success) == true) {
    /* The expression is surrounded by a matched pair of parentheses.
     * If that is the case, just throw away the parentheses.
     */
    return eval(tokens, left + 1, right - 1, success);
  }else {
    //op = the position of 主运算符 in the token expression;
    uint8_t op_type;
    uint32_t op;

    search_main_op(tokens, left, right, success, &op, &op_type);

    printf("%c %d\n", op_type, op);

    uint32_t val1 = eval(tokens, left, op - 1, success);
    uint32_t val2 = eval(tokens, op + 1, right, success);

    switch (op_type) {
      case '+': return val1 + val2;
      case '-': return val1 - val2;
      case '*': return val1 * val2;
      case '/': return val1 / val2;
      default: assert(0);
    }
  }
}


word_t expr(char *e, bool *success) {
  if (!make_token(e)) {
    *success = false;
    return 0;
  }

  for (uint8_t i = 0; i < nr_token; i ++) {
    printf("%d %s\n", tokens[i].type, tokens[i].str);
  }

  bool ans;

  ans = check_parentheses(tokens, 0, nr_token - 1, success);

  printf("ans = %d\n", ans);
  printf("success = %d\n", *success);

  uint8_t op_type;
  uint32_t op;

  search_main_op(tokens, 0, nr_token - 1, success, &op, &op_type);

  printf("%c %d\n", op_type, op);

  uint32_t res = eval(tokens, 0, nr_token - 1, success);

  printf("%d\n", res);
  /* TODO: Insert codes to evaluate the expression. */
  //TODO();

  return 0;
}
