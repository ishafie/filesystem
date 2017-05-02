/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 15:13:00 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/15 11:23:00 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strtrim(char const *s)
{
	char			*s2;
	unsigned int	i;
	int				j;
	int				k;

	i = 0;
	k = 0;
	if (s == NULL)
		return (NULL);
	j = ft_strlen(s) - 1;
	if (!(s2 = (char *)malloc(ft_strlen(s) + 1)))
		return (NULL);
	while (ft_isspace(s[i]))
		i++;
	if (s[i] == '\0')
		return (ft_strnew(1));
	while (s[k])
	{
		if (ft_isspace(s[j]))
			j--;
		k++;
	}
	j = j - i + 1;
	s2 = ft_strsub(s, i, j);
	return (s2);
}
