#include "minishell.h"
#include "tos.h"
#include "filesystem.h"

void			update_size(int sig)
{
	t_env			*env;
	struct winsize	w;

	(void)sig;
	env = get_t_env(NULL);
	ioctl(0, TIOCGWINSZ, &w);
	env->le.w_sizex = w.ws_col;
	env->le.w_sizey = w.ws_row;
}

void			stop_heredoc(int sig)
{
	t_env		*env;

	(void)sig;
	env = get_t_env(NULL);
	env->le.sig = 1;
	history(RES_ORI, NULL);
	env->le.pos_x = 4;
}

void			restart_prompt(int sig)
{
	t_env	*env;

	(void)sig;
	env = get_t_env(NULL);
	ft_putchar_fd('\n', get_fd(-1));
	display_prompt(env, NULL);
	clear_line(get_first_line(env->le.line));
	env->le.line = ft_memalloc(sizeof(t_line));
	env->le.line->is_orig = 1;
	history(RES_ORI, NULL);
	env->le.pos_x = 4;
}

static void		seg_exit(void)
{
	ft_putstr_fd("minishell: segmentation fault  ", 2);
	ft_putendl_fd(g_name_prog, 2);
}

void			safe_exit(int a)
{
	if (a == SIGINT)
		return ;
	if (a == SIGSEGV)
		seg_exit();
}
