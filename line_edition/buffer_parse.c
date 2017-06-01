#include "tos.h"

/*
***		Parsing du buffer pour l'edition de ligne standard
*/

void			parse_buffer(char *buffer, t_le *le, int mode)
{
	if (ft_isprint(buffer[0]))
		add_to_line(le, &(le->line), buffer[0]);
	else if (ft_is_arrow(buffer))
		move_cursor(le, ft_is_arrow(buffer), &(le->line), mode);
	else if (ft_is_del_or_back(buffer))
		delete_char(le, &(le->line), buffer[0]);
	else if (buffer[0] == 033 && buffer[1] == 033 && buffer[2] == '[' &&
										(buffer[3] == 'D' || buffer[3] == 'C'))
		move_to_word(buffer[3] == 'D' ? LEFT : RIGHT, le);
	else if (buffer[0] == 033 && buffer[1] == 033 && buffer[2] == '[' &&
					(buffer[3] == 'A' || buffer[3] == 'B') && mode != PAIRING)
		move_vertically(buffer[3] == 'A' ? UP : DOWN, le);
	else if (buffer[0] == 033 && buffer[1] == '[' &&
										(buffer[2] == 'H' || buffer[2] == 'F'))
		move_to_extrem(buffer[2] == 'H' ? LEFT : RIGHT, le);
	else if ((unsigned char)buffer[0] == 0xE2
			&& (unsigned char)buffer[1] == 0x88 &&
			(unsigned char)buffer[2] == 0x9A)
		clipboard_to_line(le);
	else if (buffer[0] == 4 && buffer[1] == 0)
		exit(EXIT_SUCCESS);
}
