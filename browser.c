#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int error(const char* msg) {
  perror(msg);
  exit(1);
}

int http_request(const char* addr) {
  int port = 80, in = 1;
  const char* req = "GET /\r\n";

  struct hostent* server;
  struct sockaddr_in serv_addr;
  int sockfd, bytes, sent, received, total;
  char msg[1024], resp[4096];

  if ((server = gethostbyname(addr)) == NULL) error("gethostbyname");

  memcpy(&serv_addr.sin_addr, &server->h_addr, server->h_length);
  serv_addr.sin_port = htons(port);
  serv_addr.sin_family = AF_INET;
  sockfd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  setsockopt(sockfd, IPPROTO_TCP, TCP_NODELAY, (char*)&in, sizeof(int));

  if (sockfd == -1) error("socket");

  if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) ==
      -1)
    error("connect");

  return sockfd;
}

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  return 0;
}
