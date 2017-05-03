#include "filesystem.h"

int add_folder_to_filestruct(t_fs *fs, int pos, const char *name) {
  fs->tab_inode[fs->nb_files].pos = pos;
  fs->tab_inode[fs->nb_files].file.size = 0;
  ft_strcpy(fs->tab_inode[fs->nb_files].file.name, name);
  fs->tab_inode[fs->nb_files].file.name_len = ft_strlen(name);
  fs->tab_inode[fs->nb_files].file.type = TYPEFOLDER;
  return (1);
}

void create_folder(t_fs *fs, const char *folder, int pos) {
  add_folder_to_filestruct(fs, pos, folder);
  add_to_superblock(fs);
}
