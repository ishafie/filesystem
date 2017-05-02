#include "filesystem.h"

void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd) {
  int i;

  i = 0;
  fs->fd = fd;
  fs->sb = sb;
  fs->nb_files = 0;
  fs->data = memory;
  while (i < MAXBLOC) {
    init_inode(&fs->tab_inode[i]);
    i++;
  }
}

int create_filesystem(char *fs_name, t_fs *fs)
{
  void *memory;
  int fd;
  struct stat sb;

  fd = open(fs_name, O_RDWR, 0755);
  if (fd == -1)
    err_handler("open");
  if (fstat(fd, &sb) == -1)
    err_handler("fstat");
  memory = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  if (memory == MAP_FAILED)
    err_handler("mmap");
  create_blocks(fs);
  init_filesystem(fs, memory, sb, fd);
  create_folder(fs, ".");
  return (1);
}

int add_file_to_fs(char *filename, t_fs *fs) {
  int fd;
  struct stat sb;
  char *tmp;
  int pos;

  fd = open(filename, O_RDWR, 0755);
  if (fd == -1)
    err_handler("open");
  if (fstat(fd, &sb) == -1)
    err_handler("fstat");
  pos = search_available_block(fs, sb.st_size);
  if (pos == -1) {
    err_handler("espace insuffisant.");
  }
  tmp = (char*)mmap(fs->data + pos, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  lseek(fs->fd, SEEK_SET, pos);
  write(fs->fd, tmp, sb.st_size);

  return (1);
}
