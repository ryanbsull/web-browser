#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int http_request(const char* addr) {
  int port = 80;
  const char* req = "GET /\r\n";

  struct hostent* server;
  struct sockaddr_in serv_addr;
  int sockfd, bytes, sent, received, total;
  char msg[1024], resp[4096];

  return 0;
}

int error(const char* msg) {
  perror(msg);
  exit(1);
}

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  return 0;
}
