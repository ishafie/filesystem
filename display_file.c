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
  myfolder *tmp;

  if (!fs || !fs->folder)
    return ;
  tmp = get_actual_folder(fs);
  if (fs->i_currentfolder == 0 && tmp)
    tmp = tmp->next;
  printf(".\n..\n");
  while (tmp) {
    printf("%s\n", fs->tab_inode[tmp->inode].name);
    tmp = tmp->next;
  }
}
