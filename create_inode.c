#include "filesystem.h"

void init_inode(inode *i) {
  i->pos = 0;
  i->available = TRUE;
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
void create_inode(t_fs *fs, const char *name, int i, int pos, int size, int type) {
  // comment relier un inode a ses blocks ?
  int timestamp;

  timestamp = (int)time(NULL);
  fs->tab_inode[i].available = FALSE;
  fs->tab_inode[i].pos = pos;
  fs->tab_inode[i].i_atime = timestamp;
  fs->tab_inode[i].i_mtime = timestamp;
  fs->tab_inode[i].i_ctime = timestamp;
  fs->tab_inode[i].size = size;
  fs->tab_inode[i].name_len = ft_strlen(name);
  fs->tab_inode[i].type = type;
  ft_strcpy(fs->tab_inode[i].name, name);
  if (fs->i_currentfolder != i)
    ft_strcpy(fs->tab_inode[i].path, fs->tab_inode[fs->i_currentfolder].path);
  ft_strcat(fs->tab_inode[i].path, name);
  ft_strcat(fs->tab_inode[i].path, "/");
  fs->tab_inode[i].block = NULL;
}

void create_inode_with_timestamp(t_fs *fs, const char *name, int i, int pos,
                                  int size, int type, int i_atime, int i_mtime,
                                  int i_ctime) {
  fs->tab_inode[i].available = FALSE;
  fs->tab_inode[i].pos = pos;
  fs->tab_inode[i].i_atime = i_atime;
  fs->tab_inode[i].i_mtime = i_mtime;
  fs->tab_inode[i].i_ctime = i_ctime;
  fs->tab_inode[i].size = size;
  fs->tab_inode[i].name_len = ft_strlen(name);
  fs->tab_inode[i].type = type;
  ft_strcpy(fs->tab_inode[i].name, name);
  if (fs->i_currentfolder != i)
    ft_strcpy(fs->tab_inode[i].path, fs->tab_inode[fs->i_currentfolder].path);
  ft_strcat(fs->tab_inode[i].path, name);
  ft_strcat(fs->tab_inode[i].path, "/");
  fs->tab_inode[i].block = NULL;
}
