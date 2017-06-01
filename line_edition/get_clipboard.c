#include "tos.h"

static char		*read_clipboard(void)
{
	char	buff[1024];
	int		i;
	int		fd;

	i = -1;
	if ((fd = open("/tmp/.clipboard", O_RDONLY)) == -1)
		return (NULL);
	ft_bzero(buff, sizeof(buff));
	read(fd, buff, 100);
	while (buff[++i])
	{
		if (ft_isspace(buff[i]))
			buff[i] = ' ';
	}
	close(fd);
	return (ft_strdup(buff));
}

static int		get_clipboard(void)
{
	pid_t	father;
	int		i;
	int		fd;
	char	**av;

	av = ft_memalloc(sizeof(char *) * 2);
	av[0] = ft_strdup("pbpaste");
	if ((fd = open("/tmp/.clipboard", O_WRONLY | O_CREAT | O_TRUNC, 0644)) < 0)
		return (-1);
	father = fork();
	if (father == 0)
	{
		dup2(fd, STDIN_FILENO);
		dup2(fd, STDOUT_FILENO);
		execve("/usr/bin/pbpaste", av, NULL);
	}
	else
		wait(&i);
	return (fd);
}

void			clipboard_to_line(t_le *le)
{
	char	*clipboard;
	int		i;
	int		fd;

	i = -1;
	if ((fd = get_clipboard()) != -1)
	{
		close(fd);
		if ((clipboard = read_clipboard()))
		{
			while (clipboard[++i])
				add_to_line(le, &(le->line), clipboard[i]);
			free(clipboard);
		}
	}
}
