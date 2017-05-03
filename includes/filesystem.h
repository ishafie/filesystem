#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#define BUFFER_STR 255
#define MAX_POS 9
#define MAX_SIZE 9
#define MAX_FILES 128
#define MAX_NAMELEN 3
#define SIZETOTAL 400000000
#define SIZEBLOC 1024
#define FIRSTLINE 255
#define SIZEINODELINE 277
// #define SIZEHEADER (SIZETOTAL / SIZEBLOC) * SIZEINODELINE + FIRSTLINE
#define SIZEHEADER FIRSTLINE
#define MAXBLOC (SIZETOTAL - SIZEHEADER) / SIZEBLOC
#define FALSE 0
#define TRUE 1
#define TYPEFILE 0
#define TYPEFOLDER 1

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct blocks {
	int pos;
	int available;
	int inode;
}	blocks;

typedef struct inode {
	int available;
	char inode[SIZEINODELINE];
	unsigned long pos;
	struct timespec i_atime;
  struct timespec i_mtime;
  struct timespec i_ctime;
	int size;
	int name_len;
	int type;
	char name[BUFFER_STR];
	char path[BUFFER_STR];
	struct blocks *block;
} inode;

typedef struct myfolder {
	int inode;
	int inodes[MAX_FILES];
	struct myfolder *children;
} myfolder;

typedef struct super_block {
	int pos;
} superblock;

typedef struct filesystem {
  struct stat sb;
  int nb_files;
	int i_currentfolder;
  inode tab_inode[MAXBLOC];
  void *data;
  int fd;
	blocks blocks[MAXBLOC];
	superblock s_block;
	struct myfolder *folder;
} t_fs;


int create_filesystem(char *fs_name, t_fs *fs);
void err_handler(char *err);
void init_inode(inode *i);
int add_file_to_fs(char *filename, t_fs *fs);
void create_folder(t_fs *fs, const char *folder, int pos);
int create_blocks(t_fs *fs);
int search_available_block(t_fs *fs, int size);
int add_to_superblock(t_fs *fs, struct stat sb, int pos);
void setbusy(t_fs *fs, int inode);
void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd);

#endif
