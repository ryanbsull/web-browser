#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int error(const char* msg) {
  perror(msg);
  exit(1);
}

int http_request(const char* addr) {
  printf("GET: %s\n", addr);
  int port = 80, status;
  const char* req = "GET /\r\n";
  char resp[BUFFER_SIZE];

  struct addrinfo hints = {0}, *addrs;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  if ((status = getaddrinfo(addr, "80", &hints, &addrs)) != 0) {
    char err_msg[1024];
    sprintf(err_msg, "%s: %s", addr, gai_strerror(status));
    error(err_msg);
  }
  int sockfd;

  for (struct addrinfo* addr; addr != NULL; addr = addrs->ai_next) {
    sockfd = socket(addr->ai_family, addr->ai_socktype, addr->ai_protocol);
    if (sockfd == -1) continue;
    if (connect(sockfd, addr->ai_addr, addr->ai_addrlen) == 0) break;
    close(sockfd);
    freeaddrinfo(addrs);
    error("socket");
  }

  write(sockfd, req, strlen(req));
  bzero(resp, BUFFER_SIZE);

  while (read(sockfd, resp, BUFFER_SIZE - 1) != 0) {
    printf("%s", resp);
    bzero(resp, BUFFER_SIZE);
  }

  return 0;
}

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  http_request(argv[1]);
  return 0;
}
