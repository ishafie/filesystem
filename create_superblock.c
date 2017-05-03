#include "filesystem.h"

int add_to_superblock(t_fs *fs, struct stat sb, int pos) {
  char *pos_str;

  pos_str = ft_itoa(pos);
  fseek(fs->fd, SEEK_SET, fs->s_block.pos);

  fs->s_block.pos + sb.st_size;
  return (0);
}
