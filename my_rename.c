#include "filesystem.h"

void rename_inode(t_fs *fs, int inode) {

}

int my_rename(t_fs *fs, char **args) {
  int inode;
  int nb;
  int i;

  i = 1;
  nb = 0;
  inode = -1;
  while (args[i]) {
    nb++;
    inode = search_inode_name(fs, args[i]);
    if (inode == -1)
      fprintf(stderr, "rename: cannot rename '%s': No such file or directory\n", args[i]);
    else
      rename_inode(fs, inode);
    i++;
  }
  if (nb == 0)
    fprintf(stderr, "rename: missing operand\n");
  return (1);
}
