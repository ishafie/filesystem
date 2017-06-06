#include "filesystem.h"

static int format_arg(t_fs *fs, char *arg) {
  int i;
  int begin;
  char *tmp;
  int inode;
  int prev_i_currentfolder;

  prev_i_currentfolder = fs->i_currentfolder;
  i = 0;
  begin = 0;
  inode = 0;
  while (arg[i]) {
    if (arg[i] == '/') {
      tmp = ft_strsub(arg, begin, i - begin);
      inode = search_inode_name(fs, tmp);
      if (inode == -1 || fs->tab_inode[inode].type != TYPEFOLDER) {
        fs->i_currentfolder = prev_i_currentfolder;
        return (fprintf(stderr, "'%s': No such directory\n", tmp));
      }
      fs->i_currentfolder = inode;
      ft_strdel(&tmp);
      begin = i + 1;
    }
    i++;
  }
  tmp = ft_strsub(arg, begin, i - begin);
  create_folder(fs, tmp, TRUE);
  ft_strdel(&tmp);
  fs->i_currentfolder = prev_i_currentfolder;
  return (1);
}

int my_mkdir(t_fs *fs, char **args) {
    int i;
    int nb_folder;

    nb_folder = 0;
    i = 1;
    while (args[i]) {
      nb_folder++;
      format_arg(fs, args[i]);
      i++;
    }
    if (nb_folder == 0) {
      fprintf(stderr, "mkdir: missing operand\n");
    }
    return (1);
}
