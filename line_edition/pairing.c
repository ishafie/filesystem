#include "tos.h"

/*
***		Parsing d'appairage
*/

static int		pipe_is_alone(t_line *line)
{
	while (line)
	{
		if (line->c == '|')
		{
			while (line)
			{
				if (line->c != ' ' && line->c != '\0' && line->c != '|' &&
																line->c != '\n')
					break ;
				line = line->next;
			}
			if (!line)
				return (1);
		}
		line = line->next;
	}
	return (0);
}

static char		*pair_index(char *str)
{
	if (*str == ')' || *str == '}')
		return (str - 3);
	return (str);
}

static char		reverse_pair(char c)
{
	if (c == '{')
		return ('}');
	else if (c == '(')
		return (')');
	else if (c == '[')
		return (']');
	return (c);
}

static int		search_pair(t_line *line, char f)
{
	while (line)
	{
		if (line->c == f)
		{
			line->paired = 1;
			return (1);
		}
		line = line->next;
	}
	return (0);
}

char			*missing_pair(t_line *line, int indquote)
{
	static char		prompts[7][10] = {"quote> ", "dquote> ", "subsh> ",\
										"cursh> ", "bquote> ", "glob> ", \
										"pipe> "};
	static char		missing[7] = "\'\"({`[";
	char			*find;
	int				paired;
	t_line			*first;

	first = line;
	indquote = 0;
	while (line)
	{
		paired = 0;
		indquote = (line && line->c == '\"') || indquote ? 1 : 0;
		if ((find = ft_strchr(missing, line->c)) && line->paired == 0 &&
		!(paired = search_pair(line->next, reverse_pair(line->c))) && line->c)
		{
			if (!(indquote && *find != '\"'))
				return (prompts[pair_index(find) - missing]);
		}
		else if (find && paired)
			line->paired = 1;
		line = line->next;
	}
	return (pipe_is_alone(first) ? prompts[6] : NULL);
}
