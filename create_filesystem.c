#include "filesystem.h"

/*
  GERER LE CAS FICHIER MEME NOM

*/
void testd(t_fs *fs) {
  int i;

  i = 0;
  while (i < MAXBLOC) {
    if (fs->blocks[i].available == FALSE) {
      printf("BLOCK[%d]\n", i);
      printf("pos = %d\n", fs->blocks[i].pos);
      printf("inode = %d == [%s]\n", fs->blocks[i].inode, fs->tab_inode[fs->blocks[i].inode].name);
    }
    i++;
  }
}

int ft_isnumber(const char *str) {
  int i;

  i = 0;
  while (str[i]) {
    if (!ft_isdigit(str[i])) {
      fprintf(stderr, "NaN\n");
      return (0);
    }
    i++;
  }
  return (1);
}


int close_and_return(int fd, int nb) {
  char err[10][30] =
  {
    "size of buffer",
    "maximum position",
    "maximum of time",
    "maximum of inode",
    "maximum number of files",
    "maximum of filename",
    "maximum of total size",
    "maximum of size bloc",
    "maximum of inode line"
  };

  fprintf(stderr, "Error in %s\n", err[nb]);
  close(fd);
  return (0);
}

int is_filesystem(const char *name) {
  int fd;
  char vars[10][10];
  int nbchar[10] = {3, 2, 2, 2, 2, 3, 1, 9, 4, 3};
  int i;
  int size;

  size = (int)(sizeof(vars) / sizeof(vars[0]));
  i = 0;
  while (i < size) {
    ft_bzero(vars[i], sizeof(vars[i]));
    i++;
  }
  fd = open(name, O_RDONLY, 0755);
  if (fd == -1)
    err_handler("open");
  i = 0;
  while (i < size) {
    printf("reading %d from %d\n", nbchar[i], i);
    if (read(fd, vars[i], nbchar[i]) <= 0 || !ft_isnumber(vars[i]))
      return (close_and_return(fd, i));
    i++;
  }
  G_BUFFER_STR = atoi(vars[0]);
  G_MAX_POS = atoi(vars[1]);
  G_MAX_SIZE = atoi(vars[2]);
  G_MAX_TIME = atoi(vars[3]);
  G_MAX_INODE = atoi(vars[4]);
  G_MAX_FILES = atoi(vars[5]);
  G_MAX_NAMELEN = atoi(vars[6]);
  G_SIZETOTAL = atoi(vars[7]);
  G_SIZEBLOC = atoi(vars[8]);
  G_SIZEINODELINE = atoi(vars[9]);
  close(fd);
  return (1);
}

void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd) {
  int i;
  char superblock[255];
  int i_sb;

  i_sb = 0;
  strncpy(superblock, "255", 3);
  i_sb += 3;
  strncpy(&(superblock[i_sb]), "10", 2);
  i_sb += 2;
  strncpy(&(superblock[i_sb]), "10", 2);
  i_sb += 2;
  strncpy(&(superblock[i_sb]), "10", 2);
  i_sb += 2;
  strncpy(&(superblock[i_sb]), "10", 2);
  i_sb += 2;
  strncpy(&(superblock[i_sb]), "128", 3);
  i_sb += 3;
  strncpy(&(superblock[i_sb]), "3", 1);
  i_sb += 1;
  strncpy(&(superblock[i_sb]), "400000000", 9);
  i_sb += 9;
  strncpy(&(superblock[i_sb]), "1024", 4);
  i_sb += 4;
  strncpy(&(superblock[i_sb]), "277", 3);
  i_sb += 3;
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
  strncpy(fs->data, superblock, i_sb);
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
  create_folder(fs, ".", TRUE);
  fs->i_currentfolder = 0;
  return (1);
}

int get_int(const char *mem, int *i, int size) {
  int a;
  char *local;
  int ret;

  local = (char*)malloc(sizeof(char) * size);
  if (!local)
    err_handler("malloc:");
  a = 0;
  while (a < size) {
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
  ret = atoi(local);
  free(local);
  return (ret);
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
    int inode;

    inode = 0;
    pos = *i;
    nb_blocks = 1;
    type = mem[*i];
    printf("type = [%c]\n", type);
    a = 0;
    *i += 1;
    i_atime = get_int(mem, i, MAX_TIME);
    printf("atime = [%d]\n", i_atime);
    i_mtime = get_int(mem, i, MAX_TIME);
    printf("mtime = [%d]\n", i_mtime);
    i_ctime = get_int(mem, i, MAX_TIME);
    printf("ctime = [%d]\n", i_ctime);
    size = get_int(mem, i, MAX_SIZE);
    printf("size = [%d]\n", size);
    name = get_string(mem, i, MAX_FILES);
    printf("name = [%s]\n", name);
    inodefolder = get_int(mem, i, MAX_INODE);
    printf("inodefolder = [%d]\n", inodefolder);
    printf("===STARTBLOCK===\n");
    testd(fs);
    printf("==============\n");
    printf("i = %d, nbblocks = %d\n", *i, nb_blocks);
    *i -= SIZEHEADER;
    if (type == TYPEFOLDER) {
      create_folder(fs, name, FALSE);
      *i += SIZEBLOC;
    }
    else {
      inode = 0;
      while (inode < MAXBLOC && fs->tab_inode[inode].available == FALSE) {
        inode++;
      }
      create_inode_with_timestamp(fs, name, inode, pos, size, type, i_atime, i_mtime, i_ctime);
      index_block = search_available_block(fs, size, &nb_blocks);
      a = 0;
      while (a < nb_blocks) {
        setbusy(fs, index_block + a, inode);
        *i += SIZEBLOC;
        a++;
      }
      fs->nb_files += 1;
    }
    free(name);
    printf("===ENDBLOCK===\n");
    testd(fs);
    printf("==============\n");
    //size -= FIRSTLINE;
    //*i += size;
    //printf("size : %d\n", size);
    //printf("next chars pour %d : [%c][%c][%c]\n", *i, mem[*i - 1], mem[*i + 1], mem[*i + 2]);
}

void read_blocks(t_fs *fs, const char *mem) {
  int i;

  i = FIRSTLINE;
  printf("=======> BLOCKS\n");
  //testd(fs);
  printf("start [%d]\n", i);
/*  printf("[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n[%d]\n",
  G_BUFFER_STR, G_MAX_POS, G_MAX_SIZE, G_MAX_TIME, G_MAX_INODE, G_MAX_FILES,
  G_MAX_NAMELEN, G_SIZETOTAL, G_SIZEBLOC, G_SIZEINODELINE);*/
  while (i < SIZETOTAL - 1) {
    if (mem[i] != 0) {
      get_header(fs, mem, &i);
      i -= 1;
      printf("=======> BLOCKS\n");
      //testd(fs);
      printf("========[%d] to [%d]\n", i, SIZETOTAL);
    }
    //printf("tour de boucle i = %d\n", i);
    //printf("nb files = %d\n", fs->nb_files);
    i++;
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
  write(1, "[", 1);
  write(1, memory, 200); //test
  write(1, "]\n", 2);
  init_filesystem(fs, memory, sb, fd);
  create_blocks(fs);
  read_blocks(fs, memory);
  fs->i_currentfolder = 0;
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

int add_info_line_to_fs_by_stat(t_fs *fs, struct stat sb, const char *filename, int len, int pos_of_actual_block, int nbblocks) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *nb_blocks;
  char *inodefolder;
  char type;

  atim = ft_itoa((int)(sb.st_atim.tv_sec));
  mtim = ft_itoa((int)(sb.st_mtim.tv_sec));
  ctim = ft_itoa((int)(sb.st_ctim.tv_sec));
  size = ft_itoa((int)(sb.st_size));
  nb_blocks = ft_itoa(nbblocks);
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
  printf("to %d\n", pos_of_actual_block);

  free(atim);
  free(mtim);
  free(ctim);
  free(size);
  free(inodefolder);
  free(nb_blocks);
  return (1);
}

/*
  pos_of_actual_block est la position du block selon le numéro d'inode
  il nous faut donc avoir un block différent par fichier/dossier
*/
int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, const char *filename, int len, int pos_of_actual_block, int nbblocks) {
  char *atim;
  char *mtim;
  char *ctim;
  char *size;
  char *inodefolder;
  char type;
  char *nb_blocks;

  if (len > MAX_FILES)
    err_handler("Filename length superior than max. availalble\n");
  atim = ft_itoa((int)(sb.i_atime));
  mtim = ft_itoa((int)(sb.i_mtime));
  ctim = ft_itoa((int)(sb.i_ctime));
  size = ft_itoa((int)(sb.size));
  nb_blocks = ft_itoa(nbblocks);
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
  free(nb_blocks);
  return (1);
}

int add_file_to_filestruct(t_fs *fs, const char *name, int i, int inode, int size) {

  printf("inode of tab inode = [%d] +> [%s]\n", inode, name);
  create_inode(fs, name, inode, fs->blocks[i].pos, size, 'f');
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
  int inode;

  inode = 0;
  while (inode < MAXBLOC && fs->tab_inode[inode].available == FALSE) {
    inode++;
  }
  i = 0;
  nb_blocks = 0;
  len = ft_strlen(filename);
  fd = open(filename, O_RDWR, 0755); /* OUVRIR FS */
  if (fd == -1)
    return (fprintf(stderr, "open: No such file or directory\n"));
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
  printf("=====1====\n");
  testd(fs);
  add_file_to_filestruct(fs, filename, index_block, inode, sb.st_size);
  printf("=====2====\n");
  testd(fs);
  printf("INDEX BLOCK = %d\n", index_block);
  add_info_line_to_fs_by_stat(fs, sb, filename, len, fs->blocks[index_block].pos, nb_blocks);
  printf("=====3====\n");
  testd(fs);
  strncpy(&(fs->data[fs->blocks[index_block].pos + SIZEHEADER]), tmp, sb.st_size);
  printf("=====4====\n");
  testd(fs);
  //write(fs->fd, tmp, sb.st_size);
  printf("nb blocks taken = %d\n", nb_blocks);
  while (i < nb_blocks) {
    setbusy(fs, index_block + i, inode);
    i++;
  }
  fs->nb_files += 1;
  return (1);
}
