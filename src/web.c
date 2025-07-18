#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/util.h"
#include "../include/web.h"

int http_request(const char* addr) {
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
  struct addrinfo* address = addrs->ai_next;
  for (; address != NULL; address = address->ai_next) {
    if (address->ai_family)
      sockfd = socket(address->ai_family, address->ai_socktype,
                      address->ai_protocol);
    if (sockfd == -1) continue;
    if (connect(sockfd, address->ai_addr, address->ai_addrlen) == 0) break;
    close(sockfd);
    freeaddrinfo(addrs);
    error("socket");
  }

  write(sockfd, req, strlen(req));
  bzero(resp, BUFFER_SIZE);

  int fd = open("resp.html", O_CREAT | O_RDWR);
  int len = 0, bytes = 0;
  while ((len = read(sockfd, resp, BUFFER_SIZE - 1)) != 0) {
    bytes += len;
    write(fd, resp, len);
    bzero(resp, BUFFER_SIZE);
  }

  return bytes;
}
