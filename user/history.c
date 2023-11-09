#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/console.h"

int
main(int argc, char **argv) {
  if(argc == 2) {
    int historyId = atoi(argv[1]);
    return history(historyId);
  }
  else if (argc == 1) {
    return history(-1);
  }
  else {
    printf("history command only gets one argument..\n");
    return -1;
  }
}