#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#define BUFFER_STR 255
#define MAX_POS 9
#define MAX_SIZE 9
#define MAX_FILES 128
#define MAX_NAMELEN 3
#define MAX_TIME 9
#define MAX_INODE 9
#define SIZETOTAL 400000000
#define SIZEBLOC 1024
#define TYPEFILE 0
#define TYPEFOLDER 1
#define FIRSTLINE MAX_SIZE + MAX_FILES + MAX_NAMELEN + MAX_TIME * 3 + MAX_INODE + TYPEFILE
#define SIZEINODELINE 277
#define SIZEHEADER FIRSTLINE
#define MAXBLOC ((SIZETOTAL - SIZEHEADER) / SIZEBLOC)
#define FALSE 0
#define TRUE 1
// #define SIZEHEADER (SIZETOTAL / SIZEBLOC) * SIZEINODELINE + FIRSTLINE

//dd if=/dev/zero of=mem.img  bs=1M  count=400


#include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

typedef struct blocks {
	int pos;
	int available;
	int inode;
}	blocks;

typedef struct inode {
	int available;
	char inode[SIZEINODELINE];
	int pos;
	int i_atime;
  int i_mtime;
  int i_ctime;
	int size;
	int name_len;
	int type;
	int folder_inode;
	char name[BUFFER_STR];
	char path[BUFFER_STR];
	struct blocks *block;
} inode;

typedef struct myfolder {
	int inode;
	struct myfolder *children;
	struct myfolder *next;
} myfolder;

typedef struct super_block {
	int pos;
} superblock;

typedef struct filesystem {
  struct stat sb;
  int nb_files;
	int i_currentfolder;
  inode *tab_inode; // taille maxbloc
  void *data;
  int fd;
	blocks *blocks; // taille maxbloc
	superblock s_block;
	struct myfolder *folder;
} t_fs;

void display_actual_folder(t_fs *fs);
myfolder *get_actual_folder(t_fs *fs);
void display_all_folder(t_fs *fs);
int my_ls(t_fs *fs, char **args);
int my_mkdir(t_fs *fs, char **args);
int			get_all_function(t_fs *fs, char ***args);
int search_inode_block(t_fs *fs, int inode);
int create_filesystem(char *fs_name, t_fs *fs);
void err_handler(char *err);
void init_inode(inode *i);
int add_file_to_fs(char *filename, t_fs *fs);
void create_folder(t_fs *fs, const char *folder);
int create_blocks(t_fs *fs);
int search_available_block(t_fs *fs, int size, int *nb_blocks);
int add_to_superblock(t_fs *fs, struct stat sb, int pos);
void setbusy(t_fs *fs, int i, int inode);
void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd);
int add_info_line_to_fs_by_stat(t_fs *fs, struct stat sb, const char *filename, int len, int pos_of_actual_block);
int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, const char *filename, int len, int pos_of_actual_block);
void create_inode(t_fs *fs, const char *name, int i, int pos, int size, int type);
void create_inode_with_timestamp(t_fs *fs, const char *name, int i, int pos, int size, int type, int i_atime, int i_mtime, int i_ctime);
void display_all_fs(t_fs fs);
int read_filesystem(char *fs_name, t_fs *fs);

#endif
