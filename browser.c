#include "include/util.h"
#include "include/web.h"

int main(int argc, char* argv[]) {
  if (argc != 2) error("ERROR: incorrect number of args");
  http_request(argv[1]);
  return 0;
}
