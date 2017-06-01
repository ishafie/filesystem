#include "minishell.h"

static int			my_exit_error(int a)
{
	if (a == 0)
		ft_putstr_fd("exit: too many arguments\n", 2);
	else if (a == 1)
		exit(0);
	else if (a == 2)
	{
		ft_putstr_fd("exit: number truncated after 10 digits\n", 2);
		exit(0);
	}
	return (1);
}

int					my_exit(char **args)
{
	int		i;

	i = 0;
	history(FIRST_HIST, NULL);
	history(WRITE_HIST, NULL);
	if (!args || !(*args) || !(args[1]))
		exit(0);
	if (args[1] && args[2])
		return (my_exit_error(0));
	else if (args[1])
	{
		while (args[1][i])
		{
			if (!ft_isdigit(args[1][i++]))
				return (my_exit_error(1));
		}
	}
	if (args[1] && ft_strlen(args[1]) > 10)
		return (my_exit_error(2));
	if (args[1])
		exit(ft_atoi(args[1]));
	return (1);
}
