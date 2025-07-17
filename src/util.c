#include <stdio.h>
#include <stdlib.h>

int error(const char* msg) {
  perror(msg);
  exit(1);
}

int info(const char* msg) {
  printf("INFO: %s", msg);
  exit(1);
}
