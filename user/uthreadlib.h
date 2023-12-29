#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"
#include "kernel/param.h"
#include "kernel/riscv.h"


#define FREE        0X0
#define RUNNING     0X1
#define RUNNABLE    0X2
#define STACK_SIZE  (1 << 13)
#define MAX_THREAD  4

#define TIME_QUANTUM 10

// Saved registers for kernel context switches
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