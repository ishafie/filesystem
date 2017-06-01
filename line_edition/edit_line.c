#include "tos.h"

/*
***		Gestion complete de l'edition de line
*/

t_line			*cpy_line_or_not(t_line *line, int space)
{
	t_line		*cpy;

	if (space == ADD_SPACE)
	{
		cpy = cpy_line(line);
	}
	else
		cpy = line;
	return (cpy);
}

char			*to_string(t_line *line, int space)
{
	char	buffer[2];
	char	*string;
	char	*tmp;
	t_line	*cpy;
	t_line	*first;

	string = ft_memalloc(1);
	cpy = cpy_line_or_not(line, space);
	first = cpy;
	while (cpy)
	{
		ft_bzero(buffer, sizeof(buffer));
		buffer[0] = cpy->c;
		tmp = string;
		string = ft_strjoin(string, buffer);
		free(tmp);
		cpy = cpy->next;
	}
	if (space == ADD_SPACE)
		clear_line(first);
	return (string);
}

/*
***		Changement interne de l'edition de ligne
*/

void			add_to_line(t_le *le, t_line **line, char n)
{
	t_line	*new;

	new = ft_memalloc(sizeof(t_line));
	new->x = le->pos_x + 1;
	new->y = le->pos_y;
	new->c = n;
	new->next = (*line)->next;
	new->prev = *line;
	if ((*line)->next)
		(*line)->next->prev = new;
	(*line)->next = new;
	*line = (*line)->next;
	add_to_line_display(le, line);
}

void			delete_char(t_le *le, t_line **line, char c)
{
	t_line		*tmp;

	if (!*line || (*line && (*line)->is_orig && c == 127) ||
		(c == 127 && !(*line)->prev))
		return ;
	if (c == 127 || (*line)->next == NULL)
		move_cursor(le, LEFT, line, NORMAL);
	tmp = (*line)->next;
	if ((*line)->next)
		(*line)->next = (*line)->next->next;
	if ((*line)->next)
		(*line)->next->prev = (*line);
	if (tmp)
		free(tmp);
	delete_char_display(&((*line)->next), le);
}

/*
***		Fonction principale de l'edition de ligne
***		Retourne le commande finale sous forme de liste chainee
*/

t_line			*edit_line(t_le *le)
{
	char	buffer[6];

	le->pos_x = 4;
	le->line = ft_memalloc(sizeof(t_line));
	le->line->is_orig = 1;
	history(SAVE_LINE, le->line);
	history(FIRST_HIST, NULL);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, NORMAL);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line), 0)))
		edit_line_pairing(le, le->prompt);
	le->line = get_first_line(le->line);
	return (get_first_line(le->line));
}
