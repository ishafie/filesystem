#include "minishell.h"

static void		display_time(void)
{
	time_t		rawtime;
	char		*tim;
	struct tm	*timeinfo;

	ft_putstr_fd(C_CYAN, get_fd(-1));
	ft_putchar_fd('[', get_fd(-1));
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	tim = asctime(timeinfo);
	ft_strclr(&tim[16]);
	ft_putstr_fd(&tim[11], get_fd(-1));
	ft_putstr_fd("] ", get_fd(-1));
	ft_putstr_fd(STOP, get_fd(-1));
}

void			display_prompt(t_env *e)
{
	char		*tmp;

	display_time();
	//tmp = get_usr(e);
	tmp = getenv("LOGNAME");
	ft_putstr_fd(C_BLUE, e->fd);
	if (tmp)
		ft_putstr_fd(tmp, e->fd);
	ft_putstr_fd(C_CYAN, e->fd);
	ft_putstr_fd("\n❯❯❯ ", e->fd);
	ft_putstr_fd(STOP, e->fd);
}
