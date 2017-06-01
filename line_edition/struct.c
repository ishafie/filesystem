#include "minishell.h"


t_env			*create_env(void)
{
	t_env		*tmp;

	tmp = (t_env*)malloc(sizeof(t_env));
	if (!tmp)
	{
		ft_putstr_fd("Allocation failure, exiting..\n", 2);
		exit(EXIT_FAILURE);
	}
	return (tmp);
}
