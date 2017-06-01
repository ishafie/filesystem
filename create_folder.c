#include "filesystem.h"

myfolder *new_folder(int inode) {
  myfolder *ret;

  ret = (myfolder*)malloc(sizeof(myfolder));
  if (!ret)
    err_handler("malloc");
  ret->children = NULL;
  ret->next = NULL;
  ret->inode = inode;
  return (ret);
}

int add_folder_to_filestruct(t_fs *fs, int pos, const char *name) {
  int pos_of_actual_block;

  pos_of_actual_block = search_inode_block(fs, pos);
  if (pos_of_actual_block == -1)
    pos_of_actual_block = 0;
  create_inode(fs, name, fs->nb_files, pos, 0, 'd');
  //add_info_line_to_fs_by_inode(fs, fs->tab_inode[pos], name, ft_strlen(name), pos_of_actual_block);
  fs->blocks[fs->nb_files].available = FALSE;
  fs->blocks[fs->nb_files].inode = fs->nb_files;
  fs->nb_files += 1;
  return (1);
}

void add_folder_back(myfolder **dest, int inode) {
  myfolder *tmp;

  tmp = *dest;
  if (!*dest)
    return ;
  if (!(*dest)->next) {
    (*dest)->next = new_folder(inode);
    return ;
  }
  while (tmp->next)
    tmp = tmp->next;
  tmp->next = new_folder(inode);
}

myfolder *rec_get_actual_folder(myfolder *racine, int inode) {
  myfolder *tmp;
  myfolder *ret;

  ret = NULL;
  tmp = racine;
  while (tmp) {
    if (ret != NULL)
      return (ret);
    if (tmp->inode == inode) {
      printf("found\n");
      return (tmp);
    }
    else {
      if (tmp->children)
        ret = rec_get_actual_folder(tmp->children, inode);
      tmp = tmp->next;
    }
  }
  return (NULL);
}

myfolder *get_actual_folder(t_fs *fs) {
  myfolder *ret;

  if (!fs || !fs->folder)
    return (NULL);
  ret = rec_get_actual_folder(fs->folder, fs->i_currentfolder);
  return (ret);
}

void create_folder(t_fs *fs, const char *folder) {
  int i;
  myfolder *tmp;

  tmp = NULL;
  i = 0;
  while (fs->tab_inode[i].available == 0) {
    i++;
  }
  printf("folder created at [%d]\n", i);
  add_folder_to_filestruct(fs, i, folder);
  if (!fs->folder)
    fs->folder = new_folder(i);
  else {
    printf("trying to find [%d]\n", fs->i_currentfolder);
    tmp = get_actual_folder(fs);
    if (!tmp)
      return;
    if (!tmp->next)
      tmp->next = new_folder(i);
    else
      add_folder_back(&tmp, i);
  }
  //A AJOUTER DANS LE FICHIER FILESTRUCT FILE PLUS TARD

}
