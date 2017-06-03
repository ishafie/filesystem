#include "filesystem.h"

void err_handler(char *err) {
  perror(err);
  my_exit(NULL);
}

void err_default(char *err) {
  fprintf(stderr, "%s\n", err);
  my_exit(NULL);
}
