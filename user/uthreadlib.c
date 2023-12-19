#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "user.h"
#include "uthreadlib.h"

struct thread thread_queue[MAX_THREAD];

void thread_create(void (*thread_func)(void*), void* arg) {
    void* freeptr = malloc(STACK_SIZE);
    void* stack;
    if(freeptr == 0)
        return -1;
    else
        stack = freeptr;
    
    for(int i = 0; i < MAX_THREAD; i++){
        thread_queue[i].stack_ptr = stack;
        break;
    }
    int ret = clone(thread_func, arg, stack);
    return ret;
}