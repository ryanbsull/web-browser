#include <stdio.h>
#include <stdlib.h>

int error(const char* msg) {
  perror(msg);
  exit(1);
}
