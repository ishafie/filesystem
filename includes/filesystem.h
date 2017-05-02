#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#define TOTALSIZE 400000000
#define SIZEBLOC 1024
#define MAXBLOC TOTALSIZE / SIZEBLOC

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct inode {
	unsigned long pos;
} inode;

typedef struct filesystem {
  struct stat sb;
  int nb_files;
  inode tab_inode[MAXBLOC];
  void *data;
} t_fs;

typedef struct super_block {
	unsigned long s_blocksize;
} Super_block;


int create_filesystem(char *fs_name, t_fs *fs);
void err_handler(char *err);
void init_inode(inode *i);
int add_file_to_fs(char *filename, t_fs *fs);

#endif
