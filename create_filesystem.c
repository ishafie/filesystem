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
    fs->tab_inode[i].folder_inode = -1;
    fs->tab_inode[i].available = TRUE;
    fs->tab_inode[i].pos = 0;
    fs->tab_inode[i].path[0] = 0;
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
  create_folder(fs, ".");
  fs->i_currentfolder = 0;
  return (1);
}

int get_int(const char *mem, int *i, int size) {
  int a;
  char *local;

  local = (char*)malloc(sizeof(char) * size);
  if (!local)
    err_handler("malloc:");
  a = 0;
  while (a <= size) {
    if (mem[*i] == ' ')
      break;
    local[a] = mem[*i];
    *i += 1;
    a++;
  }
  local[a] = 0;
  while (a < size) {
    *i += 1;
    a++;
  }
  printf("getint = [%s] - [%d]\n", local, a);
  return (ft_atoi(local));
}

char *get_string(const char *mem, int *i, int size) {
  int a;
  char *local;

  local = (char*)malloc(sizeof(char) * size);
  if (!local)
    err_handler("malloc:");
  a = 0;
  while (a <= size) {
    if (mem[*i] == ' ')
      break;
    local[a] = mem[*i];
    *i += 1;
    a++;
  }
  local[a] = 0;
  while (a < size) {
    *i += 1;
    a++;
  }
  printf("getstring = [%s]\n", local);
  return (local);
}

void get_header(t_fs *fs, const char *mem, int *i) {
    char *name;
    int pos;
    int size;
    int i_atime;
    int i_mtime;
    int i_ctime;
    int a;
    int type;
    int nb_blocks;
    int index_block;
    int inodefolder;

    pos = *i;
    type = mem[*i];
    if (type == TYPEFOLDER)
      fs->i_currentfolder = fs->nb_files;
    a = 0;
    *i += 1;
    i_atime = get_int(mem, i, MAX_TIME);
    i_mtime = get_int(mem, i, MAX_TIME);
    i_ctime = get_int(mem, i, MAX_TIME);
    size = get_int(mem, i, MAX_SIZE);
    name = get_string(mem, i, MAX_FILES);
    inodefolder = get_int(mem, i, MAX_INODE);
    printf("i = %d\n", *i);
    fs->i_currentfolder = inodefolder;
    create_inode_with_timestamp(fs, name, fs->nb_files, pos, size, type, i_atime, i_mtime, i_ctime);
    a = 0;
    index_block = search_available_block(fs, size, &nb_blocks);
    while (a < nb_blocks) {
      setbusy(fs, index_block + a, fs->nb_files);
      a++;
    }
    printf("i = %d\n", *i);
    free(name);
    fs->nb_files += 1;
    //size -= FIRSTLINE;
    *i += size;
    printf("size : %d\n", size);
    printf("next chars pour %d : [%c][%c][%c]\n", *i, mem[*i - 1], mem[*i + 1], mem[*i + 2]);
}

void read_blocks(t_fs *fs, const char *mem) {
  int i;

  i = 0;
  while (i < SIZETOTAL) {
    get_header(fs, mem, &i);
    printf("tour de boucle i = %d\n", i);
    if (mem[i] == 0)
      break;
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
  create_blocks(fs);
  read_blocks(fs, memory);
  /*
    READ HERE
  */
  return (1);
}


void write_according_to_field(t_fs *fs, const char *str, int len, int max, int pos) {
  char spaces[max - len];
  int i;

  i = 0;
  while (i < (max - len)) {
    spaces[i] = ' ';
    i++;
  }
  strncpy(&(fs->data[pos]), str, len);
  pos += len;
  strncpy(&(fs->data[pos]), spaces, max - len);


  //write(fd, str, len);
  //write(fd, spaces, max - len);
}

int add_info_line_to_fs_by_stat(t_fs *fs, struct stat sb, const char *filename, int len, int pos_of_actual_block) {
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
  printf("size: %d | pos: %d | total = %d\n", SIZEBLOC, pos_of_actual_block, pos_of_actual_block + SIZEBLOC);
  printf("write from %d ", pos_of_actual_block);
  strncpy(&(fs->data[pos_of_actual_block]), &type, 1);
  pos_of_actual_block++;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, atim, ft_strlen(atim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, mtim, ft_strlen(mtim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, ctim, ft_strlen(ctim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, size, ft_strlen(size), MAX_SIZE, pos_of_actual_block);
  pos_of_actual_block += MAX_SIZE;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, filename, len, MAX_FILES, pos_of_actual_block);
  pos_of_actual_block += MAX_FILES;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, inodefolder, ft_strlen(inodefolder), MAX_INODE, pos_of_actual_block);
  printf("to end\n");
  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  return (1);
}

/*
  pos_of_actual_block est la position du block selon le numéro d'inode
  il nous faut donc avoir un block différent par fichier/dossier
*/
int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, const char *filename, int len, int pos_of_actual_block) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *inodefolder;
  char type;

  if (len > MAX_FILES)
    err_handler("Filename length superior than max. availalble\n");
  atim = ft_itoa((int)(sb.i_atime));
  mtim = ft_itoa((int)(sb.i_mtime));
  ctim = ft_itoa((int)(sb.i_ctime));
  size = ft_itoa((int)(sb.size));
  inodefolder = ft_itoa(fs->i_currentfolder);
  type = sb.type ? 'd' : 'f';
  printf("size: %d | pos: %d | total = %d\n", SIZEBLOC, pos_of_actual_block, pos_of_actual_block + SIZEBLOC);
  printf("write from %d ", pos_of_actual_block);
  strncpy(&(fs->data[pos_of_actual_block]), &type, 1);
  pos_of_actual_block++;
  printf("to %d\n", pos_of_actual_block);

  /*write(fs->fd, &type, 1);*/
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, atim, ft_strlen(atim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, mtim, ft_strlen(mtim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, ctim, ft_strlen(ctim), MAX_TIME, pos_of_actual_block);
  pos_of_actual_block += MAX_TIME;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, size, ft_strlen(size), MAX_SIZE, pos_of_actual_block);
  pos_of_actual_block += MAX_SIZE;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, filename, len, MAX_FILES, pos_of_actual_block);
  pos_of_actual_block += MAX_FILES;
  printf("to %d\n", pos_of_actual_block);
  printf("write from %d ", pos_of_actual_block);
  write_according_to_field(fs, inodefolder, ft_strlen(inodefolder), MAX_INODE, pos_of_actual_block);
  printf("to end\n");
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
  //printf("nb_blocks = %d, index_block = %d\n", nb_blocks, fs->blocks[index_block].pos);
  tmp = (char*)mmap(fs->data + fs->blocks[index_block].pos, sb.st_size, PROT_WRITE, MAP_SHARED, fd, 0);
  printf("pos = %d\n", fs->blocks[index_block].pos);
  // lseek(fs->fd, SEEK_SET, fs->blocks[index_block].pos);
  add_file_to_filestruct(fs, filename, index_block, sb.st_size);
  printf("INDEX BLOCK = %d\n", index_block);
  add_info_line_to_fs_by_stat(fs, sb, filename, len, fs->blocks[index_block].pos);
  strncpy(&(fs->data[fs->blocks[index_block].pos]), tmp, sb.st_size);
  //write(fs->fd, tmp, sb.st_size);
  printf("nb blocks taken = %d\n", nb_blocks);
  while (i < nb_blocks) {
    setbusy(fs, index_block + i, fs->nb_files);
    i++;
  }
  fs->nb_files += 1;
  return (1);
}
