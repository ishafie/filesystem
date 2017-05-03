#include "filesystem.h"

void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd) {
  int i;

  i = 0;
  fs->fd = fd;
  fs->sb = sb;
  fs->nb_files = 0;
  fs->data = memory;
  fs->s_block.pos = 0;
  while (i < MAXBLOC) {
    init_inode(&fs->tab_inode[i]);
    i++;
  }
}

int create_filesystem(char *fs_name, t_fs *fs)
{
  void *memory;
  int fd;
  int fd2;
  struct stat sb;

  fd = open(fs_name, O_RDWR, 0755);
  if (fd == -1)
    err_handler("open");
  if (fstat(fd, &sb) == -1)
    err_handler("fstat");
  memory = mmap(NULL, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  if (memory == MAP_FAILED)
    err_handler("mmap");
  /* TESTS */
  fd2 = open("test.txt", O_RDWR, 0755);
  /* /TESTS */
  create_blocks(fs);
  init_filesystem(fs, memory, sb, fd2);
  create_folder(fs, ".", 0);
  fs->nb_files += 1;
  fs->i_currentfolder = 0;
  return (1);
}

int add_file_to_filestruct(t_fs *fs, int pos, struct stat sb, char *name) {

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
  /*add_file_to_filestruct(fs, pos + sb.st_size, sb, filename);
  setbusy(fs, fs->nb_files);
  add_to_superblock(fs);*/
  fs->nb_files += 1;
  return (1);
}
