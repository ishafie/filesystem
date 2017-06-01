#include "tos.h"

/*
***		Deplacement du curseur
***		ET
***		Recuperation des commandes precedentes et suivante via history()
*/

void			move_left(t_le *le, t_line **line)
{
	if (*line && (*line)->prev && !(*line)->is_orig)
	{
		*line = (*line)->prev;
		if (le->pos_x == 0)
		{
			tputs(tgetstr("up", NULL), 1, ft_putint);
			while (le->pos_x++ < le->w_sizex - 1)
				tputs(tgetstr("nd", NULL), 1, ft_putint);
			le->pos_x--;
		}
		else
		{
			le->pos_x--;
			tputs(tgetstr("le", NULL), 1, ft_putint);
		}
	}
}

void			move_right(t_le *le, t_line **line)
{
	char	buffer[1024];
	char	*buffer2;

	buffer2 = buffer;
	if ((*line)->next)
	{
		if (le->pos_x == (le->w_sizex - 1) && !(le->pos_x = 0))
			tputs(tgetstr("do", &buffer2), 1, ft_putint);
		else
		{
			tputs(tgetstr("nd", &buffer2), 1, ft_putint);
			le->pos_x++;
		}
		*line = (*line)->next;
	}
}

void			move_cursor(t_le *le, int dir, t_line **line, int mode)
{
	void	*o;
	t_line	*tmp;

	o = NULL;
	if ((dir == 2 || dir == 3) && mode != PAIRING)
	{
		move_to_first(le, line);
		tputs(tgetstr("cd", NULL), 1, ft_putint);
		tmp = get_first_line(le->line);
		le->line = dir == 2 ? history(PREV_HIST, *line) : history(NEXT_HIST, o);
		if (!tmp->is_orig)
			clear_line(tmp);
		le->pos_x = redisplay_line_index(le->line, le) - 1;
		*line = get_last_line(le->line);
	}
	else if (dir == 1)
		move_left(le, line);
	else if (dir == 4)
		move_right(le, line);
}
