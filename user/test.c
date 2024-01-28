#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

const int N = 9;

// the following does virtually nothing, but it takes a long time to execute
#define LONG_OPERATION(n) for(int i = 0; i < n*1000000; i++) __asm__ volatile("nop");

int
main(int argc, char *argv[]) {
    // create 7 processes
    fork();
    fork();
    fork();
    LONG_OPERATION(1000);
    exit(0);
}