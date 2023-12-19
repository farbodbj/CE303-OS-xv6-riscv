#include "../kernel/types.h"
#include "../kernel/proc.h"

#define FREE        0X0
#define RUNNING     0X1
#define RUNNABLE    0X2
#define STACK_SIZE  1 << 13
#define MAX_THREAD  4

struct thread {
    void* stack_ptr;
};