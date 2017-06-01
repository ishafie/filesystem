#include "minishell.h"

void		free_tab(char **str)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	while (str[len])
		len++;
	while (i < len)
	{
		free(str[i]);
		i++;
	}
}
