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
  init_filesystem(fs, memory, sb, fd);
  return (1);
}

int add_file_to_fs(char *filename, t_fs *fs) {
  int fd;
  struct stat sb;
  char *tmp;
  
  fd = open(filename, O_RDWR, 0755);
  if (fd == -1)
    err_handler("open");
  if (fstat(fd, &sb) == -1)
    err_handler("fstat");
  printf("size = %d\n", (int)sb.st_size);
  tmp = (char*)mmap(0, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  write(fs->fd, tmp, sb.st_size);
  printf("\n");
  return (1);
}
