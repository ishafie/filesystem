#include "filesystem.h"


void clear_str(char **str, int size) {
  int i;

  i = 0;
  while (i < size) {
    (*str)[i] = 0;
    i++;
  }
}

int already_exist(t_fs *fs, const char *name) {
  int i;

  i = 0;
  // compare filename & filename
  while (i <= fs->i_maxblockused) {

    if (fs->tab_inode[i].folder_inode == fs->i_currentfolder
      && strcmp(name, fs->tab_inode[i].name) == 0)
      return (1);
    i++;
  }
  return (0);
}

int cut_with_slashes(t_fs *fs, char *arg, int *i) {
  int inode;
  int begin;
  char *tmp;

  begin = 0;
  while (arg[*i]) {
    if (arg[*i] == '/') {
      tmp = ft_strsub(arg, begin, *i - begin);
      inode = search_inode_name(fs, tmp);
      if (strcmp(tmp, "..") == 0)
        fs->i_currentfolder = fs->tab_inode[fs->i_currentfolder].folder_inode;
      else if (inode == -1 || fs->tab_inode[inode].type != TYPEFOLDER) {
        fprintf(stderr, "cannot get '%s': No such directory\n", tmp);
        return (-1);
      }
      else if ((strcmp(tmp, ".") != 0))
        fs->i_currentfolder = inode;
      ft_strdel(&tmp);
      begin = *i + 1;
    }
    *i += 1;
  }
  return (begin);
}
