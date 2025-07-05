#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/parse.h"

int clean_scripts(char* resp, char** clean);
int get_headers(char* resp, char** headers);
int get_body(char* resp, char** body) {
  const char* open = "<body";
  const char* close = "</body>";
  char *start, *end;
  if ((start = strstr(resp, open))) {
    start += strlen(open);
    if ((end = strstr(start, close))) {
      *body = (char*)malloc(end - start + 1);
      memcpy(*body, start, end - start);
      (*body)[end - start] = '\0';
    }
  }

  if (!*body) return 1;

  return 0;
}
