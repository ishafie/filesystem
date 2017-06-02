#include "filesystem.h"

static void rec_display_folder(t_fs *fs, myfolder *folder) {
  myfolder *tmp;

  tmp = folder;
  while (tmp) {
    printf("%s\n", fs->tab_inode[tmp->inode].name);
    if (tmp->children)
      rec_display_folder(fs, tmp->children);
    tmp = tmp->next;
  }
}

void display_all_folder(t_fs *fs) {
  if (!fs || !fs->folder)
    return ;
  rec_display_folder(fs, fs->folder);
}

void display_actual_folder(t_fs *fs) {
  int i;

  i = 1;
  if (!fs)
    return ;
  printf(".\n..\n");
  while (i < MAX_FILES) {
    if (fs->tab_inode[i].folder_inode == fs->i_currentfolder) {
      printf("%s\n", fs->tab_inode[i].name);
    }
    i++;
  }
}
