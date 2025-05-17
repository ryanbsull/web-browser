#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int error(const char* msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  return 0;
}
