#ifndef FILESYSTEM_H
# define FILESYSTEM_H

#define BUFFER_STR 255
#define MAX_POS 10
#define MAX_SIZE 10
#define MAX_FILES 128
#define MAX_NAMELEN 3
#define MAX_TIME 10
#define MAX_INODE 10
#define SIZETOTAL 400000000
#define SIZEBLOC 1024
#define TYPEFILE 0
#define TYPEFOLDER 'd'
#define FIRSTLINE MAX_SIZE + MAX_FILES + MAX_TIME * 3 + MAX_INODE + 1
#define SIZEINODELINE 277
#define SIZEHEADER FIRSTLINE
#define MAXBLOC ((SIZETOTAL - SIZEHEADER) / SIZEBLOC)
#define MIN 0
#define MAX 1
#define FALSE 0
#define TRUE 1
// #define SIZEHEADER (SIZETOTAL / SIZEBLOC) * SIZEINODELINE + FIRSTLINE

//dd if=/dev/zero of=mem.img  bs=1M  count=400
int G_BUFFER_STR;
int G_MAX_POS;
int G_MAX_SIZE;
int G_MAX_TIME;
int G_MAX_INODE;
int G_MAX_FILES;
int G_MAX_NAMELEN;
int G_SIZETOTAL;
int G_SIZEBLOC;
int G_SIZEINODELINE;

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
  char *data;
  int fd;
	blocks *blocks; // taille maxbloc
	superblock s_block;
	struct myfolder *folder;
} t_fs;

void testd(t_fs *fs);
int display_blocks(t_fs *fs);
void reset_inode(t_fs *fs, int inode);
void clear_str(char **str, int size);
int	my_exit(char **args);
int is_filesystem(const char *name);

void get_superblock(t_fs *fs, const char *mem);

void display_actual_folder(t_fs *fs);
myfolder *get_actual_folder(t_fs *fs);
void display_all_folder(t_fs *fs);

int my_ls(t_fs *fs, char **args);
int my_mkdir(t_fs *fs, char **args);
int my_add(t_fs *fs, char **args);
int my_rm(t_fs *fs, char **args);

int	get_all_function(t_fs *fs, char ***args);
int search_block_inode(t_fs *fs, int inode);
int search_inode_block(t_fs *fs, int inode);
int search_inode_name(t_fs *fs, const char *name);
int create_filesystem(char *fs_name, t_fs *fs);
void err_handler(char *err);
void err_default(char *err);
void init_inode(inode *i);
int add_file_to_fs(char *filename, t_fs *fs);
void create_folder(t_fs *fs, const char *folder, int infs);
int create_blocks(t_fs *fs);
int search_available_block(t_fs *fs, int size, int *nb_blocks);
int add_to_superblock(t_fs *fs, struct stat sb, int pos);
void setbusy(t_fs *fs, int i, int inode);
void init_filesystem(t_fs *fs, void *memory, struct stat sb, int fd);
int _stat(t_fs *fs, struct stat sb, const char *filename, int len, int pos_of_actual_block);
int add_info_line_to_fs_by_inode(t_fs *fs, inode sb, const char *filename, int len, int pos_of_actual_block, int nbblocks);
void create_inode(t_fs *fs, const char *name, int i, int pos, int size, int type);
void create_inode_with_timestamp(t_fs *fs, const char *name, int i, int pos, int size, int type, int i_atime, int i_mtime, int i_ctime);
void display_all_fs(t_fs fs);
int read_filesystem(char *fs_name, t_fs *fs);

#endif
