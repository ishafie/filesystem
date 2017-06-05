#include "filesystem.h"

void rename_inode(t_fs *fs, int inode) {

}

int count_args(char **args) {
  int i;

  i = 0;
  while (args[i]) {
    i++;
  }
  return (i);
}

int my_rename(t_fs *fs, char **args) {
  int inode;
  int nb;
  int i;

  i = 1;
  nb = count_args(args);
  if (nb != 3)
    return (fprintf(stderr, "rename: too many/few arguments\n"));
  inode = search_inode_name(fs, args[1]);
  if (inode == -1)
    fprintf(stderr, "rename: cannot rename '%s': No such file or directory\n", args[i]);
  ft_bzero(fs->tab_inode[inode].name, sizeof(fs->tab_inode[inode].name));
  strcpy(fs->tab_inode[inode].name, args[2]);
  return (1);
}
