#include "tos.h"

void	move_to_extrem(int dir, t_le *le)
{
	if (dir == LEFT)
	{
		move_left(le, &(le->line));
		while (le->line && le->line->prev && le->pos_x && !le->line->is_orig)
			move_left(le, &(le->line));
	}
	else
	{
		move_right(le, &(le->line));
		while (le->line && le->line->next && le->pos_x < le->w_sizex - 1)
			move_right(le, &(le->line));
	}
}

void	move_vertically(int dir, t_le *le)
{
	int		init_pos;

	init_pos = le->pos_x;
	if (dir == UP)
	{
		move_left(le, &(le->line));
		while (le->line && le->line->prev && le->pos_x != init_pos)
			move_left(le, &(le->line));
	}
	else
	{
		move_right(le, &(le->line));
		while (le->line && le->line->next && le->pos_x != init_pos)
			move_right(le, &(le->line));
	}
}

void	move_to_word(int dir, t_le *le)
{
	if (dir == LEFT)
	{
		move_left(le, &(le->line));
		while (le->line && le->line->prev && le->line->c == ' ' &&
															!le->line->is_orig)
			move_left(le, &(le->line));
		while (le->line && le->line->prev && le->line->c != ' ' &&
															!le->line->is_orig)
			move_left(le, &(le->line));
	}
	else
	{
		move_right(le, &(le->line));
		while (le->line && le->line->next && le->line->prev &&
												le->line->c != ' ')
			move_right(le, &(le->line));
		while (le->line && le->line->next && le->line->c == ' ')
			move_right(le, &(le->line));
		if (le->line->prev && le->line->prev->c == ' ')
			move_left(le, &(le->line));
	}
}

void	move_to_first(t_le *le, t_line **line)
{
	while ((*line)->prev)
		move_left(le, line);
}

void	move_to_last(t_le *le, t_line **line)
{
	while ((*line)->next)
		move_right(le, line);
}
