#include "filesystem.h"

void cat_inode(t_fs *fs, int inode) {
  int pos;
  int size;

  pos = fs->blocks[inode].pos + SIZEHEADER;
  size = fs->tab_inode[inode].size;
  write(1, &(fs->data[pos]), size);
}

int my_cat(t_fs *fs, char **args) {
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
      fprintf(stderr, "cat: cannot display '%s': No such file or directory\n", args[i]);
    else
      cat_inode(fs, inode);
    i++;
  }
  if (nb == 0)
    fprintf(stderr, "cat: missing operand\n");
  return (1);
}
