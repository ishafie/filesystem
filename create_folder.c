#include "filesystem.h"

myfolder *new_folder(int inode) {
  myfolder *ret;
  int i;

  i = 0;
  ret = (myfolder*)malloc(sizeof(myfolder));
  if (!ret)
    err_handler("malloc");
  ret->children = NULL;
  while (i < MAX_FILES) {
    ret->inodes[i] = -1;
    i++;
  }
  ret->inode = inode;
  return (ret);
}

int add_folder_to_filestruct(t_fs *fs, int pos, const char *name) {

  return (1);
}

void create_folder(t_fs *fs, const char *folder, int pos) {
  int i;

  i = 0;
  while (fs->tab_inode[i].available == 0) {
    i++;
  }
  fs->folder = new_folder(i);
  add_folder_to_filestruct(fs, pos, folder);
  /*add_to_superblock(fs);*/
}
