#include "filesystem.h"

int copy_file_to_fs(t_fs *fs, int prev_inode) {
  char *tmp;
  int nb_blocks;
  int index_block;
  int index_block_prev;
  int len;
  int i;
  int inode;

  inode = 0;
  while (inode < MAXBLOC && fs->tab_inode[inode].available == FALSE) {
    inode++;
  }
  if (already_exist(fs, fs->tab_inode[prev_inode].name))
    return (fprintf(stderr, "cannot copy file %s/’: File exists\n", fs->tab_inode[prev_inode].name));
  if (inode == MAXBLOC)
    return (fprintf(stderr, "No space left in filesystem\n"));
  i = 0;
  nb_blocks = 0;
  len = ft_strlen(fs->tab_inode[prev_inode].name);
  index_block = search_available_block(fs, fs->tab_inode[prev_inode].size, &nb_blocks);
  if (index_block == -1) {
    err_handler("espace insuffisant.");
  }
  index_block_prev = search_block_inode(fs, prev_inode);
  tmp = ft_strsub(fs->data, fs->blocks[index_block_prev].pos + SIZEHEADER, fs->tab_inode[prev_inode].size); // RECUPERER LE CONTENU
  printf("tmp = [%s]\n", tmp);
  printf("pos = %d\n", fs->blocks[index_block].pos);
  add_file_to_filestruct(fs, fs->tab_inode[prev_inode].name, index_block, inode, fs->tab_inode[prev_inode].size);
  printf("INDEX BLOCK = %d\n", index_block);
  add_info_line_to_fs_by_inode(fs, fs->tab_inode[prev_inode], fs->tab_inode[prev_inode].name, len, fs->blocks[index_block].pos, nb_blocks);
  strncpy(&(fs->data[fs->blocks[index_block].pos + SIZEHEADER]), tmp, fs->tab_inode[prev_inode].size);
  printf("=====4====\n");
  testd(fs);
  printf("nb blocks taken = %d\n", nb_blocks);
  while (i < nb_blocks) {
    setbusy(fs, index_block + i, inode);
    i++;
  }
  fs->nb_files += 1;
  return (1);
}

int copy_one_file_to_folder(t_fs *fs, char **args) {
  int prev_i_currentfolder;
  int inode;
  int i;
  int inode2;
  int begin;
  char *tmp;

  inode2 = 0;
  begin = 0;
  i = 0;
  prev_i_currentfolder = fs->i_currentfolder;
  /*
    CHERCHER LE PREMIER ARGUMENT, STOCKER SON INODE DANS LA VARIABLE
    INODE.
  */
  if ((begin = cut_with_slashes(fs, args[1], &i)) == -1) {
    fs->i_currentfolder = prev_i_currentfolder;
    return (0);
  }
  tmp = ft_strsub(args[1], begin, i - begin);
  inode = search_inode_name(fs, tmp);
  if (inode == -1) {
    fs->i_currentfolder = prev_i_currentfolder;
    fprintf(stderr, "cp: cannot find '%s': No such file or directory\n", args[1]);
    return (0);
  }
  if (fs->tab_inode[inode].type == TYPEFOLDER) {
    fs->i_currentfolder = prev_i_currentfolder;
    fprintf(stderr, "cp: cannot copy directories yet\n");
    return (0);
  }
  ft_strdel(&tmp);
  fs->i_currentfolder = prev_i_currentfolder;
  /*
    CHERCHER LE DEUXIEME ARGUMENT (un dossier) ET RECUPERER SON INODE
    POUR POUVOIR STOCKER INODE1 DANS INODE2
  */
  begin = 0;
  i = 0;
  if ((begin = cut_with_slashes(fs, args[2], &i)) == -1) {
    fs->i_currentfolder = prev_i_currentfolder;
    return (0);
  }
  tmp = ft_strsub(args[2], begin, i - begin);
  inode2 = search_inode_name(fs, tmp);
  if (strcmp(tmp, "..") == 0)
    fs->i_currentfolder = fs->tab_inode[fs->i_currentfolder].folder_inode;
  else if ((strcmp(tmp, ".") == 0))
    ;
  else if (inode2 == -1 || fs->tab_inode[inode2].type != TYPEFOLDER) {
    fs->i_currentfolder = prev_i_currentfolder;
    fprintf(stderr, "cp: cannot find '%s': No such directory\n", args[2]);
    return (0);
  }
  else
    fs->i_currentfolder = inode2;
  copy_file_to_fs(fs, inode);
  fs->i_currentfolder = prev_i_currentfolder;
  return (1);
}


int my_cp(t_fs *fs, char **args) {
  int nb;

  nb = count_args(args);
  if (nb != 3)
    return (fprintf(stderr, "cp: too many/few arguments\n"));
  copy_one_file_to_folder(fs, args);
  return (1);
}
