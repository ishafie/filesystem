#include "filesystem.h"

void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd) {
  int i;

  i = 0;
  fs->tab_inode = (inode*)malloc(sizeof(inode) * MAXBLOC);
  if (!fs->tab_inode)
    err_handler("malloc:");
  fs->blocks = (blocks*)malloc(sizeof(blocks) * MAXBLOC);
  if (!fs->blocks)
    err_handler("malloc:");
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
  create_blocks(fs);
  create_folder(fs, ".", 0);
  fs->i_currentfolder = 0;
  return (1);
}

void get_header(t_fs *fs, const char *mem, int *i) {
    char *name;
    int pos;
    int size;
    int i_atime;
    int i_mtime;
    int i_ctime;
    int a;

    a = 0;
    if (mem[*i] == TYPEFILE) {
      *i += 1;
      i_atime = get_int();
      i_mtime = get_int();
      i_ctime = get_int();
      size = get_int();
      name = get_string();
      //create path
      create_inode_with_timestamp(fs, name, fs->nb_files, pos, size, TYPEFILE, i_atime, i_mtime, i_ctime);
    }
    else {
      create_folder(fs, name, fs->nb_files);
    }
    free(name);
    fs->nb_files += 1;
}

void read_blocks(t_fs *fs, const char *mem) {
  int i;

  i = 0;
  while (i < SIZETOTAL) {
    get_header(fs, mem, &i);
    //i++;
  }
}

int read_filesystem(char *fs_name, t_fs *fs) {
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
  read_blocks(fs, memory);
  /*
    READ HERE
  */
  return (1);
}


void write_according_to_field(int fd, const char *str, int len, int max) {
  char spaces[max - len];
  int i;

  i = 0;
  while (i < (max - len)) {
    spaces[i] = ' ';
    i++;
  }
  write(fd, str, len);
  write(fd, spaces, max - len);
}

int add_info_line_to_fs_by_stat(t_fs *fs, struct stat sb, const char *filename, int len) {
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
  write(fs->fd, &type, 1);
  write_according_to_field(fs->fd, atim, ft_strlen(atim), MAX_TIME);
  write_according_to_field(fs->fd, mtim, ft_strlen(mtim), MAX_TIME);
  write_according_to_field(fs->fd, ctim, ft_strlen(ctim), MAX_TIME);
  write_according_to_field(fs->fd, size, ft_strlen(size), MAX_SIZE);
  write_according_to_field(fs->fd, filename, len, MAX_FILES);
  write_according_to_field(fs->fd, inodefolder, ft_strlen(inodefolder), MAX_INODE);
  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  return (1);
}

int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, const char *filename, int len) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *inodefolder;
  char type;

  atim = ft_itoa((int)(sb.i_atime));
  mtim = ft_itoa((int)(sb.i_mtime));
  ctim = ft_itoa((int)(sb.i_ctime));
  size = ft_itoa((int)(sb.size));
  inodefolder = ft_itoa(fs->i_currentfolder);
  type = sb.type ? 'd' : 'f';
  write(fs->fd, &type, 1);
  write_according_to_field(fs->fd, atim, ft_strlen(atim), MAX_TIME);
  write_according_to_field(fs->fd, mtim, ft_strlen(mtim), MAX_TIME);
  write_according_to_field(fs->fd, ctim, ft_strlen(ctim), MAX_TIME);
  write_according_to_field(fs->fd, size, ft_strlen(size), MAX_SIZE);
  write_according_to_field(fs->fd, filename, len, MAX_FILES);
  write_according_to_field(fs->fd, inodefolder, ft_strlen(inodefolder), MAX_INODE);
  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  return (1);
}

int add_file_to_filestruct(t_fs *fs, const char *name, int i, int size) {
  create_inode(fs, name, fs->nb_files, fs->blocks[i].pos, size, 'f');
  return (1);
}

int add_file_to_fs(char *filename, t_fs *fs) {
  int fd;
  struct stat sb;
  char *tmp;
  int nb_blocks;
  int index_block;
  int len;
  int i;

  i = 0;
  nb_blocks = 0;
  len = ft_strlen(filename);
  fd = open(filename, O_RDWR, 0755); /* OUVRIR FS */
  if (fd == -1)
    err_handler("open");
  if (fstat(fd, &sb) == -1)
    err_handler("fstat");
  index_block = search_available_block(fs, sb.st_size, &nb_blocks);
  if (index_block == -1) {
    err_handler("espace insuffisant.");
  }
  printf("nb_blocks = %d, index_block = %d\n", nb_blocks, fs->blocks[index_block].pos);
  tmp = (char*)mmap(fs->data + fs->blocks[index_block].pos, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  lseek(fs->fd, SEEK_SET, fs->blocks[index_block].pos);
  add_file_to_filestruct(fs, filename, index_block, sb.st_size);
  add_info_line_to_fs_by_stat(fs, sb, filename, len);
  write(fs->fd, tmp, sb.st_size); /* ECRIRE DANS FS */
  while (i < nb_blocks) {
    printf("index_block to busy = %d\n", index_block + i);
    setbusy(fs, index_block + i, fs->nb_files);
    i++;
  }
  //add_to_superblock(fs);
  fs->nb_files += 1;
  return (1);
}
