#include "tos.h"

/*
***		Changement visuel de l'edition de ligne
*/

static void		replace_cursor(int i, t_le *le)
{
	if (le->pos_x == le->w_sizex)
	{
		tputs(tgetstr("do", NULL), 1, ft_putint);
		le->pos_x = 0;
	}
	while (i > 0)
	{
		if (le->pos_x == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			while (le->pos_x++ < le->w_sizex - 1)
				tputs(tgetstr("nd", NULL), 1, ft_putint);
		}
		else
			tputs(tgetstr("le", NULL), 1, ft_putint);
		i--;
		le->pos_x--;
	}
}

void			add_to_line_display(t_le *le, t_line **line)
{
	le->pos_x++;
	ft_putchar_fd((*line)->c, get_fd(-1));
	if (le->pos_x >= le->w_sizex)
	{
		le->pos_x = 0;
		le->pos_y++;
		tputs(tgetstr("do", NULL), 1, ft_putint);
	}
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	redisplay_line((*line)->next, le);
}

void			delete_char_display(t_line **line, t_le *le)
{
	tputs(tgetstr("cd", NULL), 1, ft_putint);
	redisplay_line(*line, le);
}

int				redisplay_line_index(t_line *line, t_le *le)
{
	t_line	*tmp;
	char	area[1024];
	int		i;
	int		x;

	i = 0;
	x = 4;
	tmp = line;
	while (tmp && i < 1024)
	{
		if (x == le->w_sizex)
			x = 0;
		area[i] = tmp->c;
		tmp = tmp->next;
		i++;
		x++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
	return (x);
}

void			redisplay_line(t_line *line, t_le *le)
{
	t_line	*tmp;
	char	area[1024];
	int		i;

	i = 0;
	tmp = line;
	while (tmp)
	{
		area[i] = tmp->c;
		if (le->pos_x == (le->w_sizex))
			le->pos_x = 0;
		le->pos_x++;
		tmp = tmp->next;
		i++;
	}
	area[i] = 0;
	write(get_fd(-1), area, i);
	replace_cursor(i, le);
}
