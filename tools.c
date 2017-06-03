#include "filesystem.h"


void clear_str(char **str, int size) {
  int i;

  i = 0;
  while (i < size) {
    (*str)[i] = 0;
    i++;
  }
}
