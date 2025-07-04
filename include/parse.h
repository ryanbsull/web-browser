#ifndef PARSE_H
#define PARSE_H

int get_headers(char* resp, char** headers);
int get_body(char* resp, char** body);

#endif
