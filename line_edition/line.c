#include "tos.h"

t_line		*cut_line_for_hist(t_line *line)
{
	int		i;
	t_line	*first;

	i = 0;
	first = line;
	while (++i < 1024 && line)
		line = line->next;
	if (line)
	{
		clear_line(line->next);
		line->next = NULL;
	}
	return (first);
}

t_line		*cpy_line(t_line *line)
{
	t_line	*cpy;
	t_line	*tmp;

	cpy = ft_memalloc(sizeof(t_line));
	line = line->next;
	tmp = cpy;
	while (line)
	{
		tmp->next = ft_memalloc(sizeof(t_line));
		tmp->next->c = line->c;
		tmp->next->prev = tmp;
		tmp = tmp->next;
		line = line->next;
	}
	return (cpy);
}

void		clear_line(t_line *line)
{
	t_line	*jeanclaude;

	jeanclaude = line;
	if (line && !(line->next))
	{
		free(line);
		return ;
	}
	while (line && line->next)
	{
		jeanclaude = line;
		line = line->next;
		free(jeanclaude);
	}
	free(line);
	line = NULL;
}
