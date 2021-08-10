#include "watchpoint.h"
#include "expr.h"

#include <stdlib.h>

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = &wp_pool[i + 1];
  }
  wp_pool[NR_WP - 1].next = NULL;

  head = NULL;
  free_ = wp_pool;
}

/* TODO: Implement the functionality of watchpoint */

WP* new_wp() {
  if (free_ == NULL) assert(0);

  WP* p;
  
  p = free_;

  free_ = free_->next;
  
  if (head == NULL) {
    p->next = NULL;
  } else {
    p->next = head;
  }
  
  head = p;

  return head;
}

void free_wp(WP* wp) {
  WP* p;

  p = head;
  
  if (head == wp) {
    head = p->next;
  } else {
    while(p != NULL && p->next != wp) {
      p = p->next;
    }

    p->next = p->next->next;   
  }

  wp->val = 0;
  free(wp->expr);

  wp->next = free_;
  free_ = wp;
}

WP* del_wp(int no, bool* flag) {
  WP* p = head;
  
  while(p != NULL && p->NO != no) {
    p = p->next;
  }

  if (p == NULL) *flag = false;

  return p;
}

void print_w() {
  WP* p = head;

  if (p == NULL) {
    printf("No watchpoints.\n");
  } else {
    printf("Num\tWhat\tVal\n");
    while(p) {
      printf("%d\t%s\t%d\n", p->NO, p->expr, p->val);
      p = p->next;
    }
  }
}