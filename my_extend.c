#include "filesystem.h"

int my_extend(t_fs *fs, char **args) {
  int nb;
  int inode;
  int index_block;
  int pos;
  int len;
  int nb_blocks;
  int size;

  nb = count_args(args);
  if (nb != 3)
    return (fprintf(stderr, "extend: too many/few arguments\n"));
  inode = search_inode_name(fs, args[1]);
  if (inode == -1)
    return (fprintf(stderr, "extend: cannot extend '%s': No such file\n", args[1]));
  else if (fs->tab_inode[inode].type == TYPEFOLDER)
    return (fprintf(stderr, "extend: cannot extend folders !\n"));
  index_block = search_block_inode(fs, inode);
  if (index_block == -1)
    return (0);
  len = strlen(args[2]);
  pos = fs->blocks[index_block].pos + SIZEHEADER + fs->tab_inode[inode].size;
  printf("begin = %d => HEADER = %d => size = %d => pos = %d\n", fs->blocks[index_block].pos, SIZEHEADER, fs->tab_inode[inode].size, pos);
  size = (fs->tab_inode[inode].size + len);
  nb_blocks = size / SIZEBLOC;
  if (size % SIZEBLOC != 0 || size == 0)
    nb_blocks++;
  if (pos + len < fs->blocks[index_block + 1].pos) {
    strncpy(&fs->data[pos], args[2], len);
    fs->tab_inode[inode].size += len;
    add_info_line_to_fs_by_inode(fs, fs->tab_inode[inode], fs->tab_inode[inode].name, strlen(fs->tab_inode[inode].name), fs->blocks[index_block].pos, nb_blocks);
  }
  else {
    printf("extending to next block\n");
    if (fs->blocks[index_block + 1].available == TRUE) {
      strncpy(&fs->data[pos], args[2], len);
      setbusy(fs, index_block + 1, inode);
      fs->tab_inode[inode].size += len;
      add_info_line_to_fs_by_inode(fs, fs->tab_inode[inode], fs->tab_inode[inode].name, strlen(fs->tab_inode[inode].name), fs->blocks[index_block].pos, nb_blocks);
    }
    else {
      fprintf(stderr, "extend: no blocks available for extending\n");
    }
  }
  return (1);
}
