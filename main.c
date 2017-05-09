#include "filesystem.h"

void display_all_fs(t_fs fs) {
  int i;

  i = 0;
  printf("nb_files = %d\n", fs.nb_files);
  printf("i_currentfolder = %d\n", fs.i_currentfolder);
  printf("====FILES====\n");
  while (i < fs.nb_files) {
    if (fs.tab_inode[i].available == FALSE) {
      printf("==INODE[%d]==\n", i);
      printf("pos = %d\n", fs.tab_inode[i].pos);
      printf("timestamp a = %d\n", fs.tab_inode[i].i_atime);
      printf("timestamp m = %d\n", fs.tab_inode[i].i_mtime);
      printf("timestamp c = %d\n", fs.tab_inode[i].i_ctime);
      printf("size = %d\n", fs.tab_inode[i].size);
      printf("name_len = %d\n", fs.tab_inode[i].name_len);
      if (fs.tab_inode[i].type == TYPEFILE)
        printf("FILE\n");
      else
        printf("FOLDER\n");
      printf("name = %s\n", fs.tab_inode[i].name);
      printf("path = %s\n", fs.tab_inode[i].path);
    }
    i++;
  }
  i = 0;
  while (i < MAXBLOC) {
    if (fs.blocks[i].available == FALSE) {
      printf("==BLOCK[%d]==\n", i);
      printf("pos = %d\n", fs.blocks[i].pos);
      printf("inode = %d\n", fs.blocks[i].inode);
    }
    i++;
  }
}

int main(int argc, char** argv) {
  t_fs fs;

  (void)argc;
  (void)argv;
  create_filesystem("mem.img", &fs);
  add_file_to_fs("toto.txt", &fs);
  add_file_to_fs("tutu.txt", &fs);
  add_file_to_fs("greatfile.txt", &fs);
  add_file_to_fs("toto.txt", &fs);
  display_all_fs(fs);
	return 0;
}
