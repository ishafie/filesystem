#include "tos.h"
#include "minishell.h"
#include "filesystem.h"

void display_all_fs(t_fs fs) {
  int i;

  i = 0;
  printf("nb_files = %d\n", fs.nb_files);
  printf("i_currentfolder = %d\n", fs.i_currentfolder);
  printf("====FILES====\n");
  while (i < fs.nb_files) {
    if (fs.tab_inode[i].available == FALSE) {
      printf("==INODE[%d]==\n", i);
      printf("pos = %d\n", fs.tab_inode[i].pos);
      printf("timestamp a = %d\n", fs.tab_inode[i].i_atime);
      printf("timestamp m = %d\n", fs.tab_inode[i].i_mtime);
      printf("timestamp c = %d\n", fs.tab_inode[i].i_ctime);
      printf("size = %d\n", fs.tab_inode[i].size);
      printf("name_len = %d\n", fs.tab_inode[i].name_len);
      if (fs.tab_inode[i].type == TYPEFILE)
        printf("FILE\n");
      else
        printf("FOLDER\n");
      printf("name = %s\n", fs.tab_inode[i].name);
      printf("path = %s\n", fs.tab_inode[i].path);
    }
    i++;
  }
  i = 0;
  while (i < MAXBLOC) {
    if (fs.blocks[i].available == FALSE) {
      printf("==BLOCK[%d]==\n", i);
      printf("pos = %d\n", fs.blocks[i].pos);
      printf("inode = %d\n", fs.blocks[i].inode);
    }
    i++;
  }
}

int			get_all_function(t_fs *fs, char ***args)
{
	if (!args || !(*args) || !((*args)[0]))
		return (0);
	if (ft_strcmp((*args)[0], "exit") == 0)
		return (my_exit(*args));
  else if (ft_strcmp((*args)[0], "mkdir") == 0)
    return (my_mkdir(fs, *args));
  else if (ft_strcmp((*args)[0], "ls") == 0)
    return (my_ls(fs, *args));
  else if (ft_strcmp((*args)[0], "add") == 0)
    return (my_add(fs, *args));
  else if (ft_strcmp((*args)[0], "rm") == 0)
    return (my_rm(fs, *args));
    else if (ft_strcmp((*args)[0], "blocks") == 0)
      return (display_blocks(fs));
	return (0);
}

int 		split_and_use_commands(char *line, t_fs *fs) {
	char **cmd;

	cmd = ft_strsplit_space(line);
	if (!cmd || !cmd[0])
		return (0);
	get_all_function(fs, &cmd);
	return (1);
}

void exec_dd(char *dd, char *zero, char *name, char *sizeone, char *size) {
  char *makefs[] = {dd, zero, name, sizeone, size, NULL};

  execvp(makefs[0], makefs);
}

void create_file(char **argv, int argc, t_fs *fs) {
  char namedd[256];
  char name[256];
  char size[10];
  int status;

  status = 0;
  strcpy(name, "mem.img");
  strcpy(size, "count=400");
  strcpy(namedd, "of=mem.img");
  if (fork() == 0) {
    if (argc > 2) {
      ft_bzero(&name, sizeof(name));
      ft_bzero(&namedd, sizeof(namedd));
      strcpy(name, argv[2]);
      strcpy(namedd, "of=");
      strcat(namedd, argv[2]);
      namedd[strlen(argv[2]) + 3] = 0;
      if (argc > 3) {
        ft_bzero(&size, sizeof(size));
        strcpy(size, "count=");
        strcat(size, argv[3]);
        size[strlen(argv[3]) + 6] = 0;
      }
    }
    printf("namedd = %s\nsize=%s\n", namedd, size);
    exec_dd("dd", "if=/dev/zero", namedd, "bs=1M", size);
  }
  else {
    wait(&status);
    if (status != 0) {
      err_default("echec de la création du filesystem.");
    }
    create_filesystem(name, fs);
  }
}

void install_filesystem(int argc, char **argv, t_fs *fs) {
  if (argc < 2) {
    create_file(argv, argc, fs);
    return ;
  }
  else {
    if (strcmp(argv[1], "create") == 0) {
      create_file(argv, argc, fs);
    }
    else if (argc > 2 && strcmp(argv[1], "read") == 0 && is_filesystem(argv[2])) {
      read_filesystem(argv[2], fs);
    }
    else
      err_default("Invalid arguments.");
    return ;
  }
}

int			loop_prompt(int argc, char **argv, t_env *e)
{
	char	*line;
	t_line	*add_to_hist;
	t_env	*env;
	t_fs fs;

	line = NULL;
	env = get_t_env(NULL);
  install_filesystem(argc, argv, &fs);
	while (42)
	{
		display_prompt(e);
		signal(SIGINT, restart_prompt);
		init_term();
		add_to_hist = edit_line(&(e->le));
		reset_term(env->reset);
		signal(SIGINT, safe_exit);
		line = to_string(add_to_hist, ADD_SPACE);
		split_and_use_commands(line, &fs); // tout le programme est ici
		history(FIRST_HIST, NULL);
		history(ADD_HIST, add_to_hist);
	}
}

int		main(int argc, char **argv)
{
	struct termios		reset;
	t_le				le;
	t_env				*data_env;

  G_BUFFER_STR = 0;
  G_MAX_POS = 0;
  G_MAX_SIZE = 0;
  G_MAX_TIME = 0;
  G_MAX_INODE = 0;
  G_MAX_FILES = 0;
  G_MAX_NAMELEN = 0;
  G_SIZETOTAL = 0;
  G_SIZEBLOC = 0;
  G_SIZEINODELINE = 0;
	if (tcgetattr(0, &reset) == -1)
		message_handling();
	g_name_prog = NULL;
	signal(SIGWINCH, update_size);
	data_env = create_env();
	data_env->reset = reset;
	//fill_env(&data_env, env);
	if (init_term() == 0)
		message_handling();
	init_env(&le, data_env);
	data_env->le = le;
	loop_prompt(argc, argv, data_env);
	//free_env(&data_env);
	reset_term(reset);
	return (0);
}
