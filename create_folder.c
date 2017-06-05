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
  int index_block;
  int nb_blocks;

  nb_blocks = 0;
  index_block = search_available_block(fs, 0, &nb_blocks);
  pos_of_actual_block = fs->blocks[index_block].pos;
  printf("index block = %d\n", index_block);
  printf("pos before = %d & inode = %d\n", pos_of_actual_block, pos);
  if (pos_of_actual_block == -1)
    pos_of_actual_block = 0;
  printf("pos now = %d\n", pos_of_actual_block);
  create_inode(fs, name, pos, fs->blocks[index_block].pos, 0, 'd');
  add_info_line_to_fs_by_inode(fs, fs->tab_inode[pos], name, ft_strlen(name), pos_of_actual_block, nb_blocks);
  fs->nb_files += 1;
  write(1, "[", 1);
  write(1, fs->data, 3000); //test
  write(1, "]\n", 2);
  fs->blocks[index_block].available = FALSE;
  fs->blocks[index_block].inode = pos;
  return (1);
}

int add_folder_to_struct(t_fs *fs, int pos, const char *name) {
  int pos_of_actual_block;
  int index_block;
  int nb_blocks;

  nb_blocks = 0;
  index_block = search_available_block(fs, 0, &nb_blocks);
  pos_of_actual_block = fs->blocks[index_block].pos;
  printf("index block = %d\n", index_block);
  printf("pos before = %d & inode = %d\n", pos_of_actual_block, pos);
  if (pos_of_actual_block == -1)
    pos_of_actual_block = 0;
  create_inode(fs, name, pos, fs->blocks[index_block].pos, 0, 'd');
  fs->nb_files += 1;
  fs->blocks[index_block].available = FALSE;
  fs->blocks[index_block].inode = pos;
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

void create_folder(t_fs *fs, const char *folder, int infs) {
  int i;
  myfolder *tmp;

  tmp = NULL;
  i = 0;
  while (i < MAXBLOC && fs->tab_inode[i].available == FALSE) {
    i++;
  }
  printf("inode dispo = %d\n", i);
  if (infs)
    add_folder_to_filestruct(fs, i, folder);
  else
    add_folder_to_struct(fs, i, folder);
  if (!fs->folder)
    fs->folder = new_folder(i);
  else {
    tmp = get_actual_folder(fs);
    if (!tmp)
      return;
    if (!tmp->next)
      tmp->next = new_folder(i);
    else
      add_folder_back(&tmp, i);
  }

}
