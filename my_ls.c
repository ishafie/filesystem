#include "filesystem.h"

int my_ls(t_fs *fs, char **args) {
  (void)fs;
  (void)args;
  printf("doing ls\n");
  display_actual_folder(fs);
  return (1);
}
