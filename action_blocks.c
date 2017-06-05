#include "filesystem.h"

int display_blocks(t_fs *fs) {
  testd(fs);
  return (1);
}

int search_available_block(t_fs *fs, int size, int *nb_blocks) {
  int i;
  int begin;

  begin = 0;
  i = 0;
  printf("size = %d\n", size);
  while (i < MAXBLOC) {
    begin = i;
    while (i < MAXBLOC && fs->blocks[i].available == TRUE && (i - begin) * SIZEBLOC < size) {
      i++;
    }
    if ((i - begin) * SIZEBLOC >= size && fs->blocks[begin].available == TRUE) {
      if (size == 0)
        *nb_blocks = 1;
      else
        *nb_blocks = i - begin;
      return (begin);
    }
    i++;
  }
  return (-1);
}

int search_inode_block(t_fs *fs, int inode) {
    int i;

    i = 0;
    while (i < MAXBLOC) {
      if (inode < i)
        return (-1);
      if (inode == fs->blocks[i].inode) {
        printf("blocks pos = %d\n", fs->blocks[i].pos);
        return (fs->blocks[i].pos);
      }
      i++;
    }
    return (-1);
}

int search_block_inode(t_fs *fs, int inode) {
  int i;

  i = 0;
  while (i < MAXBLOC) {
    if (inode == fs->blocks[i].inode) {
      return (i);
    }
    i++;
  }
  return (-1);
}

int search_inode_name(t_fs *fs, const char *name) {
  int i;

  i = 0;
  while (i < MAXBLOC) {
    if (strcmp(name, fs->tab_inode[i].name) == 0 && fs->tab_inode[i].folder_inode == fs->i_currentfolder)
      return (i);
    i++;
  }
  return (-1);
}

void setbusy(t_fs *fs, int i, int inode) {
  fs->blocks[i].available = FALSE;
  fs->blocks[i].inode = inode;
  if (i > fs->i_maxblockused)
    fs->i_maxblockused = i;
}
