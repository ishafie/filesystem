#include "filesystem.h"

void empty_str(char *str, char c, int len) {
  int i;

  i = 0;
  while (i < len) {
    str[i] = c;
    i++;
  }
}
/*
  DELETE PUIS CHECK BLOCK ET ON VOIT CE QUI VA PAS  !
*/
int delete_inode(t_fs *fs, int inode) {
  int pos[2];
  int size;
  int nb_blocks;
  int inodemax;
  int old_inode;

  old_inode = inode;
  pos[MIN] = fs->blocks[inode].pos;
  size = fs->tab_inode[inode].size;
  nb_blocks = (size / SIZEBLOC);
  if (size % SIZEBLOC != 0 || size == 0)
    nb_blocks++;
  inode = search_block_inode(fs, inode); // actually index_block, not inode
  inodemax = inode + nb_blocks;
  if (inode == -1 || old_inode == 0)
    return (0);
  reset_inode(fs, old_inode);
  if (fs->i_maxblockused <= inodemax)
    fs->i_maxblockused = inode;
  while (inode < inodemax) {
    fs->blocks[inode].available = TRUE;
    fs->blocks[inode].inode = -1;
    inode++;
  }
  pos[MAX] = fs->blocks[inode].pos;
  empty_str(&(fs->data[pos[MIN]]), 0, pos[MAX] - pos[MIN]);
  fs->nb_files--;
  return (1);
}

int delete_all_inode_folder(t_fs *fs, int inode, int maxblock) {
  int i;

  i = 1;
  while (i <= maxblock) {
    if (fs->tab_inode[i].folder_inode == inode) {
      if (fs->tab_inode[i].type == TYPEFOLDER)
        delete_all_inode_folder(fs, i, maxblock);
      delete_inode(fs, i);
    }
    i++;
  }
  return (1);
}

int delete_all_inode(t_fs *fs, int inode) {
  if (fs->tab_inode[inode].type != TYPEFOLDER)
    return (delete_inode(fs, inode));
  else {
    delete_all_inode_folder(fs, inode, fs->i_maxblockused);
    delete_inode(fs, inode);
  }
  return (1);
}

int my_rm(t_fs *fs, char **args) {
  int inode;
  int nb;
  int i;

  i = 1;
  nb = 0;
  inode = -1;
  while (args[i]) {
    nb++;
    inode = search_inode_name(fs, args[i]);
    if (inode <= 0)
      fprintf(stderr, "rm: cannot remove '%s': No such file or directory\n", args[i]);
    else
      delete_all_inode(fs, inode);
    i++;
  }
  if (nb == 0)
    fprintf(stderr, "rm: missing operand\n");
  return (1);
}
