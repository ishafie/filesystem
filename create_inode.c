#include "filesystem.h"

void reset_inode(t_fs *fs, int i) {
  fs->tab_inode[i].folder_inode = -1;
  fs->tab_inode[i].available = TRUE;
  fs->tab_inode[i].pos = -1;
  fs->tab_inode[i].i_atime = 0;
  fs->tab_inode[i].i_mtime = 0;
  fs->tab_inode[i].i_ctime = 0;
  fs->tab_inode[i].size = 0;
  fs->tab_inode[i].name_len = 0;
  fs->tab_inode[i].type = 0;
  ft_bzero(fs->tab_inode[i].name, sizeof(fs->tab_inode[i].name));
  ft_bzero(fs->tab_inode[i].path, sizeof(fs->tab_inode[i].path));
}

void create_inode(t_fs *fs, const char *name, int i, int pos, int size, int type) {
  // comment relier un inode a ses blocks ?
  int timestamp;

  timestamp = (int)time(NULL);
  fs->tab_inode[i].folder_inode = fs->i_currentfolder;
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
  /*ft_strcat(fs->tab_inode[i].path, name);
  ft_strcat(fs->tab_inode[i].path, "/");*/
}

void create_inode_with_timestamp(t_fs *fs, const char *name, int i, int pos,
                                  int size, int type, int i_atime, int i_mtime,
                                  int i_ctime) {
  fs->tab_inode[i].folder_inode = fs->i_currentfolder;
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
  /*ft_strcat(fs->tab_inode[i].path, name);
  ft_strcat(fs->tab_inode[i].path, "/");*/
}
