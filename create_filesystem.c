#include "filesystem.h"

void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd) {
  int i;

  i = 0;
  fs->fd = fd;
  fs->sb = sb;
  fs->nb_files = 0;
  fs->data = memory;
  fs->s_block.pos = 0;
  fs->i_currentfolder = 0;
  fs->folder = NULL;
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


void write_according_to_field(int fd, char *str, int len, int max) {
  char zeros[max];
  int i;

  i = 0;
  while (i < max) {
    zeros[i] = 0;
    i++;
  }
  write(fd, str, len);
  write(fd, zeros, max);
}

int add_info_line_to_fs_by_stat(t_fs *fs, struct stat sb, char *filename, int len) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *inodefolder;
  char type;

  atim = ft_itoa((int)(sb.st_atim.tv_sec));
  mtim = ft_itoa((int)(sb.st_mtim.tv_sec));
  ctim = ft_itoa((int)(sb.st_ctim.tv_sec));
  size = ft_itoa((int)(sb.st_size));
  inodefolder = ft_itoa(fs->i_currentfolder);
  if (S_ISREG(sb.st_mode))
    type = 'f';
  else
    type = 'd';
  printf("%s\n", atim);
  printf("%s\n", mtim);
  printf("%s\n", ctim);
  write_according_to_field(fs->fd, atim, ft_strlen(atim), MAX_TIME);
  write_according_to_field(fs->fd, mtim, ft_strlen(mtim), MAX_TIME);
  write_according_to_field(fs->fd, ctim, ft_strlen(ctim), MAX_TIME);
  write_according_to_field(fs->fd, size, ft_strlen(size), MAX_SIZE);
  write(fs->fd, &type, 1);
  write_according_to_field(fs->fd, filename, len, MAX_FILES);
  write_according_to_field(fs->fd, inodefolder, ft_strlen(inodefolder), MAX_INODE);
  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  return (1);
}

int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, char *filename, int len) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *inodefolder;
  char type;

  atim = ft_itoa((int)(sb.i_atime.tv_sec));
  mtim = ft_itoa((int)(sb.i_mtime.tv_sec));
  ctim = ft_itoa((int)(sb.i_ctime.tv_sec));
  size = ft_itoa((int)(sb.size));
  inodefolder = ft_itoa(fs->i_currentfolder);
  type = sb.type ? 'd' : 'f';
  printf("%s\n", atim);
  printf("%s\n", mtim);
  printf("%s\n", ctim);
  write_according_to_field(fs->fd, atim, ft_strlen(atim), MAX_TIME);
  write_according_to_field(fs->fd, mtim, ft_strlen(mtim), MAX_TIME);
  write_according_to_field(fs->fd, ctim, ft_strlen(ctim), MAX_TIME);
  write_according_to_field(fs->fd, size, ft_strlen(size), MAX_SIZE);
  write(fs->fd, &type, 1);
  write_according_to_field(fs->fd, filename, len, MAX_FILES);
  write_according_to_field(fs->fd, inodefolder, ft_strlen(inodefolder), MAX_INODE);
  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  return (1);
}


int add_file_to_fs(char *filename, t_fs *fs) {
  int fd;
  struct stat sb;
  char *tmp;
  int pos;
  int len;

  len = ft_strlen(filename);
  fd = open(filename, O_RDWR, 0755); /* OUVRIR FS */
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
  add_info_line_to_fs_by_stat(fs, sb, filename, len);
  write(fs->fd, tmp, sb.st_size); /* ECRIRE DANS FS */
  /*add_file_to_filestruct(fs, pos + sb.st_size, sb, filename);
  setbusy(fs, fs->nb_files);
  add_to_superblock(fs);*/
  fs->nb_files += 1;
  return (1);
}
