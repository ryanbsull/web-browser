#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parse.h"

static int clean_scripts(char* body) {
  const char* open = "<script";
  const char* close = "</script>";
  int len = strlen(open);
  if (len > 0) {
    char* p = body;
    size_t size = 0;
    while ((p = strstr(p, open)) != NULL) {
      p = strstr(p, close);
      size = (size == 0) ? (p - body) + strlen(p + len) + 1 : size - len;
      memmove(p, p + len, size - (p - body));
    }
  }
  return 0;
}

int get_headers(char* resp, char** headers) {
  int size = 0;
  while (resp[size + 1] != '<' && resp[size + 2] != '!') size++;
  *headers = (char*)malloc(size + 1);
  memcpy(*headers, resp, size);
  (*headers)[size] = '\0';

  if (!*headers) return 1;

  return 0;
}

int get_body(char* resp, char** body) {
  const char* open = "<body";
  const char* close = "</body>";
  char *start, *end;
  if ((start = strstr(resp, open))) {
    start += strlen(open);
    while (start[0] != '>') start++;
    start++;
    if ((end = strstr(start, close))) {
      *body = (char*)malloc(end - start + 1);
      memcpy(*body, start, end - start);
      (*body)[end - start] = '\0';
    }
  }

  if (!*body) return 1;
  // if (clean_scripts(*body)) return 1;

  return 0;
}
