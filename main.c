#include "filesystem.h"

int main(int argc, char** argv) {
  t_fs fs;

  (void)argc;
  (void)argv;
  create_filesystem("mem.img", &fs);
  /*add_file_to_fs("toto.txt", &fs);*/
	return 0;
}
