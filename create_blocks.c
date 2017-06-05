#include "filesystem.h"

int create_blocks(t_fs *fs) {
  int pos;
  int i;

  i = 0;
  pos = SIZEHEADER;
  while (i < MAXBLOC) {
    fs->blocks[i].pos = pos;
    fs->blocks[i].available = TRUE;
    fs->blocks[i].inode = -1;
    pos += SIZEBLOC;
    i++;
  }
  return (1);
}
