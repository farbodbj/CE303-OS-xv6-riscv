#include "uthreadlib.h"

// the following does virtually nothing, but it takes a long time to execute
#define LONG_OPERATION(n) for(int i = 0; i < n*1000000; i++) __asm__ volatile("nop");

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

// this function is both the scheduler and the operation for showing the thread's progress
void thread_function() {
    int start = uptime();
    int thread_id = current_thread->context.s0;
    int counter = current_thread->context.s1;
    for(; counter <= 100; counter++){

        LONG_OPERATION(counter);
        printf("thread_%d %d\n", thread_id, counter);

        // the if statement performs the role of a scheduler tick interrupt
        if(uptime() - start >= TIME_QUANTUM) {
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

    thread_create(thread_function, 1);
    thread_create(thread_function, 2);
    thread_create(thread_function, 3);

    thread_schedule();
    return 0;
}