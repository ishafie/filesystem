#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#define SIZETOTAL 400000000
#define SIZEBLOC 1024
#define FIRSTLINE 255
#define SIZEHEADER (SIZETOTAL / SIZEBLOC) + FIRSTLINE
#define MAXBLOC (SIZETOTAL - SIZEHEADER) / SIZEBLOC
#define TRUE 1
#define FALSE 0

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct my_file {
	int inode_n;
	int size;
	int name_len;
	int type;
	char name[255];
} my_file;

typedef struct inode {
	unsigned long pos;
} inode;

typedef struct blocks {
	int pos;
	int available;
}	blocks;

typedef struct filesystem {
  struct stat sb;
  int nb_files;
  inode tab_inode[MAXBLOC];
  void *data;
  int fd;
	blocks blocks[MAXBLOC];
} t_fs;

typedef struct super_block {
	unsigned long s_blocksize;
} Super_block;


int create_filesystem(char *fs_name, t_fs *fs);
void err_handler(char *err);
void init_inode(inode *i);
int add_file_to_fs(char *filename, t_fs *fs);
void create_folder(t_fs *fs, const char *folder);
int create_blocks(t_fs *fs);
int search_available_block(t_fs *fs, int size);

#endif
