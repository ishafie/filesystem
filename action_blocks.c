#include "filesystem.h"

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
    if ((i - begin) * SIZEBLOC >= size) {
      *nb_blocks = i - begin;
      return (begin);
    }
    i++;
  }
  return (-1);
}

void setbusy(t_fs *fs, int i, int inode) {
  fs->blocks[i].available = FALSE;
  fs->blocks[i].inode = inode;
}
