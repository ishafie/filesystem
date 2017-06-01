#include "minishell.h"

void			free_args(char **args)
{
	int		i;

	i = 0;
	while (args[i] != NULL)
	{
		free(args[i]);
		args[i] = NULL;
		i++;
	}
}
