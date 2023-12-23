#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/param.h"
#include "kernel/riscv.h"


struct context {
   uint64 ra;
   uint64 sp;
   uint64 s0;
   uint64 s1;
   uint64 s2;
   uint64 s3;
   uint64 s4;
   uint64 s5;
   uint64 s6;
   uint64 s7;
   uint64 s8;
   uint64 s9;
   uint64 s10;
   uint64 s11;
};

#define FREE        0X0
#define RUNNING     0X1
#define RUNNABLE    0X2
#define STACK_SIZE  (1 << 13)
#define MAX_THREAD  4

// Thread structure
struct thread {
   char stack[STACK_SIZE];
   int state;
   struct context context;
};


// Array of all threads
struct thread all_thread[MAX_THREAD];
struct thread *current_thread;

void thread_switch(struct context*, struct context*);


void thread_init(void) {
   current_thread = all_thread;
   current_thread->state = RUNNING;
}

void thread_schedule(void) {
    struct thread *t, *next_thread;
    next_thread = 0;
    t = current_thread + 1;
    for (int i = 0; i < MAX_THREAD; i++) {
        if (t >= all_thread + MAX_THREAD) t = all_thread;
        if (t->state == RUNNABLE) {
            next_thread = t;
            break;
        }
        t = t + 1;
    }
    if (next_thread == 0) {
        printf("thread_schedule: no runnable threads\n");
        exit(-1);
    }
    if (current_thread != next_thread) {
        next_thread->state = RUNNING;
        struct thread *temp = current_thread;
        current_thread = next_thread;
        thread_switch(&temp->context, &current_thread->context);
    }
}


void thread_yield(void) {
   current_thread->state = RUNNABLE;
   thread_schedule();
}


void thread_create(void (*func)(), int tid) {
  struct thread *t;
  for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
      if (t->state == FREE) break;
  }
  t->state = RUNNABLE;
  memset(&t->context, 0, sizeof(t->context));
  t->context.ra = (uint64)func;
  t->context.sp = (uint64)(t->stack + STACK_SIZE);
  t->context.s0 = (uint64)(tid);
}

void thread_join(void) {
  while (current_thread->state != FREE) {
      thread_yield();
  }
}

void function() {
    int start = uptime();
    int thread_id = current_thread->context.s0;
    int counter = current_thread->context.s1;
    for(; counter <= 100; counter++){
        printf("thread_%d %d\n", thread_id, counter);
        if(uptime() - start >= 1) {
            start = uptime();
            thread_yield();
        }
    }
    current_thread->state = FREE;
    memset(current_thread, 0, sizeof(struct thread));
    thread_schedule();
    return;
}

int main(int *argc, char **argv[]) {
    thread_init();

    thread_create(function, 1);
    thread_create(function, 2);
    thread_create(function, 3);

    thread_schedule();
    return 0;
}