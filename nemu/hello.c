#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define NR_WP 32
#define NULL ((void *)0)

typedef struct watchpoint {
  int NO;
  char* expr;
  u_int32_t val;
  struct watchpoint *next;

  /* TODO: Add more members if necessary */

} WP;

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
  WP* q;

  p = head;
  
  if (p->NO == wp->NO) {
    head = p->next;

    free(p);
  } else {
    while(p->next->NO != wp->NO) {
      p = p->next;
    }

    q = p->next;

    p->next = q->next;

    free(q);    
  }
}

void print_w() {
  WP* p = head;

  while(p) {
    printf("[Watchpoint NO.%d] %s\n", p->NO, p->expr);
    p = p->next;
  }
}

int main() {
  init_wp_pool();

  WP *wp = new_wp();
  wp->expr = (char*)malloc(sizeof("123"));
  strcpy(wp->expr, "123");

  wp = new_wp();
  wp->expr = (char*)malloc(sizeof("123"));
  strcpy(wp->expr, "123");

  print_w();
}