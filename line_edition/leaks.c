#include "tos.h"

int				end_is_not_in_line(t_le *le, char *end)
{
	char		*tmp;

	tmp = to_string(get_orig_line(le->line), NORMAL);
	if (ft_strcmp(tmp, end) && !le->sig)
	{
		free(tmp);
		return (1);
	}
	free(tmp);
	return (0);
}
