#include <isa.h>
#include "expr.h"
#include "watchpoint.h"

#include <stdlib.h>
#include <memory/paddr.h>
#include <readline/readline.h>
#include <readline/history.h>

//void cpu_exec(uint64_t);
//int is_batch_mode();
//
///* We use the `readline' library to provide more flexibility to read from stdin. */
//static char* rl_gets() {
//  static char *line_read = NULL;
//
//  if (line_read) {
//    free(line_read);
//    line_read = NULL;
//  }
//
//  line_read = readline("(nemu) ");
//
//  if (line_read && *line_read) {
//    add_history(line_read);
//  }
//
//  return line_read;
//}
//
//static int cmd_c(char *args) {
//  cpu_exec(-1);
//  return 0;
//}
//
//static int cmd_q(char *args) {
//  return -1;
//}
//
//static int cmd_x(char *args) {
//  char *arg1 = strtok(NULL, " ");
//  char *arg2 = args + strlen(args) + 1;
//  
//  bool success = true;
//
//  paddr_t addr = expr(arg2, &success);
//
//  //sscanf(arg2, "%x", &addr);
//  printf("%s\n", arg1);
//  printf("%u\n", addr);
//  //uint8_t i;
//  //uint8_t len;
//  
//  //for (i = 0, len = atoi(arg1); i < len; i ++) {
//  //  printf("%#x 0x%08x\n", addr + (i * 4), paddr_read(addr + (i * 4), 4));
//  //}
//
//  return 0;
//}
//
//static int cmd_si(char *args) {
//  char *arg = strtok(NULL, " ");
//  uint64_t n = arg ? atoi(arg) : 1;
//
//  if (n != 0) {
//    cpu_exec(n);
//  } else {
//    printf("Unknown command format of 'si'\n");
//  }
//
//  return 0;
//}
//
//static int cmd_info(char *args) {
//  char *arg = strtok(NULL, " ");
//
//  if (arg && strcmp(arg, "r") == 0) {
//    isa_reg_display();
//  } else {
//    printf("Unknown command format of 'info'\n");
//  }
//
//  return 0;
//}
//
//static int cmd_help(char *args);
//
//static struct {
//  char *name;
//  char *description;
//  int (*handler) (char *);
//} cmd_table [] = {
//  { "help", "Display informations about all supported commands", cmd_help },
//  { "c", "Continue the execution of the program", cmd_c },
//  { "q", "Exit NEMU", cmd_q },
//  { "x", "Examine memory", cmd_x },
//  { "si", "Execute N instructions in a single step", cmd_si },
//  { "info", "print registers informations", cmd_info },
//  /* TODO: Add more commands */
//
//};
//
//#define NR_CMD (sizeof(cmd_table) / sizeof(cmd_table[0]))
//
//static int cmd_help(char *args) {
//  /* extract the first argument */
//  char *arg = strtok(NULL, " ");
//  int i;
//
//  if (arg == NULL) {
//    /* no argument given */
//    for (i = 0; i < NR_CMD; i ++) {
//      printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
//    }
//  }
//  else {
//    for (i = 0; i < NR_CMD; i ++) {
//      if (strcmp(arg, cmd_table[i].name) == 0) {
//        printf("%s - %s\n", cmd_table[i].name, cmd_table[i].description);
//        return 0;
//      }
//    }
//    printf("Unknown command '%s'\n", arg);
//  }
//  return 0;
//}
//
//void ui_mainloop() {
//  if (is_batch_mode()) {
//    cmd_c(NULL);
//    return;
//  }
//
//  for (char *str; (str = rl_gets()) != NULL; ) {
//    char *str_end = str + strlen(str);
//
//    /* extract the first token as the command */
//    char *cmd = strtok(str, " ");
//    if (cmd == NULL) { continue; }
//
//    /* treat the remaining string as the arguments,
//     * which may need further parsing
//     */
//    char *args = cmd + strlen(cmd) + 1;
//    if (args >= str_end) {
//      args = NULL;
//    }
//
//#ifdef HAS_IOE
//    extern void sdl_clear_event_queue();
//    sdl_clear_event_queue();
//#endif
//
//    int i;
//    for (i = 0; i < NR_CMD; i ++) {
//      if (strcmp(cmd, cmd_table[i].name) == 0) {
//        if (cmd_table[i].handler(args) < 0) { return; }
//        break;
//      }
//    }
//
//    if (i == NR_CMD) { printf("Unknown command '%s'\n", cmd); }
//  }
//}

void ui_mainloop() {
  bool success = true;
  word_t ans = expr("1+1", &success);
  printf("%d", ans);
}