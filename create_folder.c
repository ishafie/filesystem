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
  int pos;
  inode ino;

  //remplir ino
  create_inode(fs);
  pos = search_available_block(fs, FIRSTLINE);
  add_info_line_to_fs_by_inode(fs, ino, char *filename, int len)
  return (1);
}

void create_folder(t_fs *fs, const char *folder, int pos) {
  int i;

  i = 0;
  while (fs->tab_inode[i].available == 0) {
    i++;
  }
  if (!fs->folder)
    fs->folder = new_folder(i);
  else {
    printf("TODO : children\n");
  }
  add_folder_to_filestruct(fs, pos, folder);
  /*add_to_superblock(fs);*/
}
