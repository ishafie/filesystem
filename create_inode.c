#include "filesystem.h"

void init_inode(inode *i) {
  i->pos = 0;
}
/*
int fill_inode(char inode[SIZEINODELINE], char *name, int max, int index) {
  int i;

  i = 0;
  while (index < SIZEINODELINE && i < max && name[i]) {
    inode[index] = name[i];
    index++;
    i++;
  }
  while (i < max && index < SIZEINODELINE) {
    inode[index] = 0;
    index++;
    i++;
  }
  return (index);
}

void create_inode(t_fs *fs, int i) {
  char *pos_str;
  char *size_str;
  char *name_len;
  char type;
  int index;

  index = 0;
  pos_str = ft_itoa(fs->tab_inode[i].pos);
  size_str = ft_itoa(fs->tab_inode[i].file.size);
  name_len = ft_itoa(fs->tab_inode[i].file.name_len);
  type = fs->tab_inode[i].type;
  index = fill_inode(fs->tab_inode[i].inode, pos_str, MAX_POS);
  index = fill_inode(fs->tab_inode[i].inode, pos_str, MAX_SIZE);
  index = fill_inode(fs->tab_inode[i].inode, pos_str, MAX_NAMELEN);
  fs->tab_inode[i].inode[index] = fs->tab_inode[i].type;
  free(pos_str);
  free(size_str);
  free(name_len);
}
*/
