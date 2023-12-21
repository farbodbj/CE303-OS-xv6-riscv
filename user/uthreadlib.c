#include "uthreadlib.h"


void thread_init(void) {
   current_thread = &all_thread[0];
}

// void thread_create(void (*func)()) {
//    struct thread *t;
//    for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
//        if (t->state == FREE) break;
//    }
//    t->state = RUNNABLE;
//    memset(&t->context, 0, sizeof(t->context));
//    t->context.ra = (uint64)func;
//    t->context.sp = (uint64)(t->stack + STACK_SIZE);
// }

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


void thread_create(void (*func)()) {
  struct thread *t;
  for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
      if (t->state == FREE) break;
  }
  t->state = RUNNABLE;
  memset(&t->context, 0, sizeof(t->context));
  t->context.ra = (uint64)func;
  t->context.sp = (uint64)(t->stack + STACK_SIZE);
}

void thread_join(void) {
  while (current_thread->state != FREE) {
      thread_yield();
  }
}