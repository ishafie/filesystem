#include "filesystem.h"

void err_handler(char *err) {
  perror(err);
  exit(EXIT_FAILURE);
}
