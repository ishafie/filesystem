#include "filesystem.h"

int go_to_prev(t_fs *fs) {
  fs->i_currentfolder = fs->tab_inode[fs->i_currentfolder].folder_inode;
  return (1);
}

int my_cd(t_fs *fs, char **args) {
  int nb;
  int inode;

  nb = count_args(args);
  if (nb != 2)
    return (fprintf(stderr, "cd: too many/few arguments\n"));
  if (strcmp(args[1], "..") == 0) {
    return (go_to_prev(fs));
  }
  inode = search_inode_name(fs, args[1]);
  if (inode == -1 || fs->tab_inode[inode].type != TYPEFOLDER)
    return (fprintf(stderr, "cd: cannot cd to '%s': No such directory\n", args[1]));
  //if (is_child(fs, inode))
  fs->i_currentfolder = inode;
  return (1);
}
