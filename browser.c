#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "include/parse.h"
#include "include/util.h"
#include "include/web.h"

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  int len = http_request(argv[1]);
  char *buffer = (char*)malloc(len), *body = NULL, *headers = NULL;
  int fd = open("resp.html", O_CREAT | O_RDWR);
  if (read(fd, buffer, len) < 0g return 1;
  if (get_headers(buffer, &headers) || get_body(buffer, &body)) {
    printf("ERROR: could not parse response\n");
    return 1;
  } else {
    printf("%s\n", headers);
    printf("%s\n", body);
  }
  return 0;
}
