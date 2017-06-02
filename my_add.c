#include "filesystem.h"

int     my_add(t_fs *fs, char **args) {
  int i;

  i = 1;
  while (args[i]) {
    add_file_to_fs(args[i], fs);
    i++;
  }
  return (1);
}
