#include "tos.h"

int		ft_putint(int c)
{
	write(get_fd(-1), &c, 1);
	return (1);
}
