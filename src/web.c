#include <arpa/inet.h>
#include <fcntl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip_icmp.h>
#include <netinet/tcp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#include "../include/util.h"
#include "../include/web.h"

char *dns_lookup(const char *addr_host, struct sockaddr_in *addr_con) {
  printf("\nResolving DNS...\n");
  struct hostent *host_entity;
  char *ip = (char *)malloc(NI_MAXHOST * sizeof(char));

  if ((host_entity = gethostbyname(addr_host)) == NULL) {
    // No IP found for hostname
    return NULL;
  }

  // Fill up address structure
  strcpy(ip, inet_ntoa(*(struct in_addr *)host_entity->h_addr));
  (*addr_con).sin_family = host_entity->h_addrtype;
  (*addr_con).sin_port = htons(PORT);
  (*addr_con).sin_addr.s_addr = *(long *)host_entity->h_addr;

  return ip;
}

int http_request(const char *addr) {
  int port = 80, status;
  const char *req = "GET /\r\n";
  char resp[BUFFER_SIZE];

  struct sockaddr_in req_addr;
  char *addr_ip = dns_lookup(addr, &req_addr);
  if (addr_ip == NULL) error("DNS FAILED");
  return 1;
}
