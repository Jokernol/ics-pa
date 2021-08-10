#ifndef __WATCHPOINT_H__
#define __WATCHPOINT_H__

#include <common.h>

typedef struct watchpoint {
  int NO;
  char *expr;
  uint32_t val;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

} WP;

WP* new_wp();

void free_wp(WP* wp);

WP* del_wp(int no, bool* flag);

void print_w();

bool check_wp();

#endif
 