#include "filesystem.h"

int search_available_block(t_fs *fs, int size) {
  int i;
  int begin;

  begin = 0;
  i = 0;
  while (i < MAXBLOC) {
    begin = i;
    while (i < MAXBLOC && fs->blocks[i].available == TRUE) {
      i++;
    }
    if ((i - begin) * SIZEBLOC >= size)
      return (begin);
    i++;
  }
  return (-1);
}
