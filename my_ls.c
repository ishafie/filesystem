#include "filesystem.h"

int is_flag(char *str, char flag) {
  if (!str || !str[0] || !str[1] || str[2] ||
    str[0] != '-' || str[1] != flag)
    return (0);
  return (1);
}

void print_type(t_fs *fs, int i) {
  if (fs->tab_inode[i].type == TYPEFOLDER) {
    printf("%c ", 'd');
  }
  else
    printf("%c ", 'f');
}

void print_size(t_fs *fs, int i, int spaces) {
  printf("%*d ", spaces, fs->tab_inode[i].size);
}

void print_date(t_fs *fs, int i, int which) {
  char timestr[50];
  char *str;

  ft_bzero(timestr, sizeof(timestr));
  str = ctime(&(fs->tab_inode[i].i_ctime));
  strncpy(timestr, &str[4], 12);
  if (which == CREATION) {
    printf("[%s] ", timestr);
  }
}

int lensize(int size) {
  int i;

  i = 0;
  while (size > 0) {
    size /= 10;
    i++;
  }
  return (i);
}

int check_spaces(t_fs *fs) {
  int i;
  int max;
  int nb;

  nb = 0;
  max = 0;
  i = 0;
  while (i < MAX_FILES) {
    if (fs->tab_inode[i].folder_inode == fs->i_currentfolder) {
      nb = lensize(fs->tab_inode[i].size);
      if (max < nb)
        max = nb;
    }
    i++;
  }
  return (max);
}

void display_folder_with_flags(t_fs *fs, int flags[]) {
  int i;
  int sizemaxlen;

  i = 1;
  if (!fs)
    return ;
  sizemaxlen = check_spaces(fs);
  if (flags[L] == TRUE) {
    print_type(fs, 0);
    print_date(fs, 0, CREATION);
    print_size(fs, 0, sizemaxlen);
  }
  printf(".\n");
  if (flags[L] == TRUE) {
    print_type(fs, 0);
    print_date(fs, 0, CREATION);
    print_size(fs, 0, sizemaxlen);
  }
  printf("..\n");
  while (i < MAX_FILES) {
    if (fs->tab_inode[i].folder_inode == fs->i_currentfolder) {
      if (flags[L] == TRUE) {
        //-rw-rw-r-- 1 tikko tikko        11 May  8 15:45 tutu.txt
        print_type(fs, i);
        print_date(fs, i, CREATION);
        print_size(fs, i, sizemaxlen);
      }
      printf("%s\n", fs->tab_inode[i].name);
    }
    i++;
  }
}

static int format_arg(t_fs *fs, char *arg, int flags[]) {
  int prev_i_currentfolder;
  int inode;
  int i;
  int begin;
  char *tmp;

  i = 0;
  prev_i_currentfolder = fs->i_currentfolder;
  if ((begin = cut_with_slashes(fs, arg, &i)) == -1) {
    fs->i_currentfolder = prev_i_currentfolder;
    return (0);
  }
  tmp = ft_strsub(arg, begin, i - begin);
  inode = search_inode_name(fs, tmp);
  if (strcmp(tmp, "..") == 0)
    fs->i_currentfolder = fs->tab_inode[fs->i_currentfolder].folder_inode;
  else if (inode == -1 || fs->tab_inode[inode].type != TYPEFOLDER) {
    fs->i_currentfolder = prev_i_currentfolder;
    fprintf(stderr, "ls: cannot display '%s': No such directory\n", tmp);
    return (0);
  }
  else if ((strcmp(tmp, ".") != 0))
    fs->i_currentfolder = inode;
  ft_strdel(&tmp);
  display_folder_with_flags(fs, flags);
  fs->i_currentfolder = prev_i_currentfolder;
  return (1);
}

void display_different_folder_with_flag(t_fs *fs, char **args, int flags[]) {
  int i;

  i = 1;
  while (args[i]) {
    if (args[i][0] != '-') {
      format_arg(fs, args[i], flags);
    }
    i++;
  }
}

void check_flags(char **args, int flags[]) {
  int i;

  i = 1;
  while (args[i]) {
    if (is_flag(args[i], 'l'))
      flags[L] = TRUE;
    else if (is_flag(args[i], 'f'))
      flags[F] = TRUE;
    else
      flags[2] = TRUE;
    i++;
  }
}

int my_ls(t_fs *fs, char **args) {
  int flags[3];

  ft_bzero(flags, sizeof(flags));
  check_flags(args, flags);
  if (flags[2] == TRUE)
    display_different_folder_with_flag(fs, args, flags);
  else
    display_folder_with_flags(fs, flags);
  return (1);
}
