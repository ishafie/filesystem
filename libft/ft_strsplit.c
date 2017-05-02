/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 16:29:50 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/26 22:09:08 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		nb_word(char const *s, char c)
{
	int			i;
	int			k;

	k = 0;
	i = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (s[i] != c)
			k++;
		while (s[i] != c && s[i])
			i++;
		if (s[i] == c)
			i++;
	}
	return (k);
}

static char		*nblet(char const *s, char c, const int j)
{
	int			i;
	int			k;
	int			m;
	int			o;

	m = j;
	k = 0;
	i = 0;
	while (m >= 0)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c && m > 0)
			i++;
		m--;
	}
	o = i;
	while (s[i] != c && s[i])
	{
		k++;
		i++;
	}
	return (ft_strsub(s, o, k));
}

char			**ft_strsplit(char const *s, char c)
{
	int			i;
	char		**tab;
	int			j;

	if (!s)
		return (NULL);
	j = 0;
	i = nb_word(s, c);
	if (!(tab = (char **)ft_memalloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (i)
	{
		tab[j] = nblet(s, c, j);
		i--;
		j++;
	}
	tab[j] = 0;
	return (tab);
}
