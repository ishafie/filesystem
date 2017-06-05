#include "filesystem.h"

int my_mkdir(t_fs *fs, char **args) {
    int i;
    int nb_folder;

    nb_folder = 0;
    i = 1;
    while (args[i]) {
      nb_folder++;
      create_folder(fs, args[i], TRUE); //need pos
      i++;
    }
    if (nb_folder == 0) {
      fprintf(stderr, "mkdir: missing operand\n");
    }
    (void)fs;
    return (1);
}
