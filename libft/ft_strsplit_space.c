/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit_space.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 20:51:07 by ishafie           #+#    #+#             */
/*   Updated: 2016/05/26 22:09:20 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int		get_next_quote(char const *s, int i)
{
	int			save;

	save = i;
	while (s[i] && s[i] != 34)
		i++;
	if (s[i] == 34)
		return (i);
	else
		return (save - 1);
}

static int		nb_word(char const *s)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (ft_isspace(s[i]))
		i++;
	while (s[i])
	{
		if (s[i] == 34)
			i = get_next_quote(s, i + 1);
		if (!ft_isspace(s[i]))
			k++;
		while (!ft_isspace(s[i]) && s[i])
			i++;
		if (ft_isspace(s[i]))
			i++;
	}
	return (k);
}

static int		nbhelp(char const *s, int j, int *i_quote)
{
	int			i;

	i = 0;
	if (s[i] == 34 && i > *i_quote)
	{
		*i_quote = i;
		return (i + 1);
	}
	while (j >= 0)
	{
		while (ft_isspace(s[i]) && s[i])
			i++;
		if (s[i] == 34 && i > *i_quote)
		{
			*i_quote = i;
			return (i + 1);
		}
		while (!ft_isspace(s[i]) && s[i] && j > 0)
			i++;
		j--;
	}
	return (i);
}

static char		*nblet(char const *s, const int j, int *i_quote)
{
	int			i;
	int			k;
	int			o;

	k = 0;
	o = 0;
	i = nbhelp(s, j, i_quote);
	o = i;
	if ((i - 1) > 0 && s[i - 1] == 34)
	{
		k = i;
		i = get_next_quote(s, i);
		k = i - k;
	}
	while (!ft_isspace(s[i]) && s[i] && s[i] != 34)
	{
		k++;
		i++;
	}
	if (k == -1)
		k = 0;
	return (ft_strsub(s, o, k));
}

char			**ft_strsplit_space(char const *s)
{
	int			i;
	char		**tab;
	int			j;
	int			i_quote;

	i_quote = -1;
	if (!s)
		return (NULL);
	j = 0;
	i = nb_word(s);
	tab = (char **)ft_memalloc(sizeof(char *) * (i + 1));
	if (tab == NULL)
		return (NULL);
	while (i)
	{
		tab[j] = nblet(s, j, &i_quote);
		i--;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
