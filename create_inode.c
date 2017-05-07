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
*/
void create_inode(t_fs *fs, char *name, int i, int pos, int size, int type) {
  // comment relier un inode a ses blocks ?
  fs->tab_inode[i].available = FALSE;
  fs->tab_inode[i].pos = pos;
  fs->tab_inode[i].i_atime = ;
  fs->tab_inode[i].i_mtime = ;
  fs->tab_inode[i].i_ctime = ;
  fs->tab_inode[i].size = size;
  fs->tab_inode[i].name_len = ft_strlen(name);
  fs->tab_inode[i].type = type;
  ft_strcpy(fs->tab_inode[i].name, name);
  if (fs->i_currentfolder != i)
    ft_strcpy(fs->tab_inode[i].path, fs->tab_inode[fs->[i_currentfolder]].path);
  ft_strcat(fs->tab_inode[i].path, name);
  ft_strcat(fs->tab_inode[i].path, "/");
  fs->tab_inode[i].blocks = NULL;
}
