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

int			get_all_function(char ***args)
{
	if (!args || !(*args) || !((*args)[0]))
		return (0);
	if (ft_strcmp((*args)[0], "exit") == 0)
		return (my_exit(*args));
	return (0);
}

int 		split_and_use_commands(char *line, t_fs *fs) {
	char **cmd;

	cmd = ft_strsplit_space(line);
	if (!cmd || !cmd[0])
		return (0);
	printf("%s\n", line);
	get_all_function(&cmd);
	(void)fs;
	/*
  add_file_to_fs("toto.txt", &fs);
  add_file_to_fs("tutu.txt", &fs);
  add_file_to_fs("greatfile.txt", &fs);
  add_file_to_fs("toto.txt", &fs);*/
  /*read_filesystem("mem.img", &fs);*/
  //display_all_fs(fs);
	return (1);
}

int			loop_prompt(t_env *e)
{
	char	*line;
	t_line	*add_to_hist;
	t_env	*env;
	t_fs fs;

	line = NULL;
	env = get_t_env(NULL);
	(void)fs;
	//create_filesystem("mem.img", &fs);
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

int		main(int ac, char **av, char **env)
{
	struct termios		reset;
	t_le				le;
	t_env				*data_env;

	(void)ac;
	(void)av;
	(void)env;
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
	loop_prompt(data_env);
	//free_env(&data_env);
	reset_term(reset);
	return (0);
}
