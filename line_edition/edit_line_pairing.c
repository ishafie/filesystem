#include "tos.h"

/*
***		gere l'appairage de certains caracteres recursivement
*/

static void			create_first_line(t_le *le, int bsn)
{
	if (!bsn || !le->line)
		le->line = ft_memalloc(sizeof(t_line));
	else
	{
		le->line->next = ft_memalloc(sizeof(t_line));
		le->line->next->prev = le->line;
		le->line = le->line->next;
	}
	le->line->c = bsn ? '\n' : 0;
	le->line->is_orig = 1;
}

void				edit_line_pairing(t_le *le, char *prompt)
{
	char	buffer[6];

	le->pos_x = ft_strlen(prompt);
	ft_putstr_fd(prompt, get_fd(-1));
	create_first_line(le, 1);
	while (42)
	{
		ft_bzero(buffer, sizeof(buffer));
		read(0, buffer, 5);
		parse_buffer(buffer, le, PAIRING);
		if (buffer[0] == '\n' && buffer[1] == 0)
		{
			move_to_last(le, &(le->line));
			tputs(tgetstr("do", NULL), 1, ft_putint);
			break ;
		}
	}
	if ((le->prompt = missing_pair(get_first_line(le->line), 0)))
		edit_line_pairing(le, le->prompt);
}
