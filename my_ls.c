#include "filesystem.h"

int my_ls(t_fs *fs, char **args) {
  (void)args;
  display_actual_folder(fs);
  return (1);
}
