#include "uthreadlib.c"

void thread_a(void) {
  for (int i = 0; i < 100; i++) {
      printf("thread_a %d\n", i);
      thread_yield();
  }
  printf("thread_a: exit after 100\n");
  current_thread->state = FREE;
}

void thread_b(void) {
  for (int i = 0; i < 100; i++) {
      printf("thread_b %d\n", i);
      thread_yield();
  }
  printf("thread_b: exit after 100\n");
  current_thread->state = FREE;
}

void thread_c(void) {
  for (int i = 0; i < 100; i++) {
      printf("thread_c %d\n", i);
      thread_yield();
  }
  printf("thread_c: exit after 100\n");
  current_thread->state = FREE;
}

int main(void) {
  thread_init();
  thread_create(thread_a);
  thread_create(thread_b);
  thread_create(thread_c);
  while (1) {
      thread_yield();
  }
  return 0;
}
