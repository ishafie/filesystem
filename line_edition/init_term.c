#include "tos.h"
#include "minishell.h"

int				init_term(void)
{
	char				area[512];
	char				*tmp;
	char				*name_term;
	struct termios		term;
	int					fd;

	fd = open(ttyname(2), O_RDWR);
	if (fd == -1)
		fd = 2;
	get_fd(fd);
	tmp = area;
	if (tcgetattr(0, &term) == -1)
		return (0);
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSADRAIN, &term) == -1)
		return (0);
	if (getenv("TERM") == NULL)
		return (0);
	name_term = getenv("TERM");
	if (tgetent(NULL, name_term) == ERR)
		return (0);
	tputs(tgetstr("am", &tmp), 1, ft_putint);
	tputs(tgetstr("xn", &tmp), 1, ft_putint);
	return (1);
}

int				reset_term(struct termios reset)
{
	struct termios		term;

	term = reset;
	if (tcsetattr(0, 0, &term) == -1)
		return (0);
	return (1);
}

static void		init_fd(t_le *e)
{
	int				fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd == -1)
		fd = 2;
	e->fd = fd;
}

void			calc_col(t_le *e)
{
	struct winsize	win;
	int				fd;

	fd = open("/dev/tty", O_RDWR);
	if (fd == -1)
		ioctl(0, TIOCGWINSZ, &win);
	else
		ioctl(fd, TIOCGWINSZ, &win);
	e->w_sizex = win.ws_col;
	e->w_sizey = win.ws_row;
}

void			init_env(t_le *e, t_env *env)
{
	get_t_env(env);
	init_fd(e);
	calc_col(e);
	get_pos_cursor(&(e->pos_x), &(e->pos_y));
	history(READ_HIST, NULL);
	env->fd = get_fd(-1);
}
