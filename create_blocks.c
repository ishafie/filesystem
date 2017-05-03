#include "filesystem.h"

void display_blocks(blocks b[MAXBLOC]) {
  int i;

  i = 0;
  while (i < MAXBLOC) {
    printf("blocks pos = %d\n", b[i].pos);
    i++;
  }
}


int create_blocks(t_fs *fs) {
  blocks *b;
  int pos;
  int i;

  i = 0;
  pos = SIZEHEADER;
  b = NULL;
  while (i < MAXBLOC) {
    fs->blocks[i].pos = pos;
    fs->blocks[i].available = TRUE;
    fs->blocks[i].inode = 0;
    pos += SIZEBLOC;
    i++;
  }
  return (1);
}
