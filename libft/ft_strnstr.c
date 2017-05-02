/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:57:52 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/07 17:41:06 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *s1, const char *s2, size_t n)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (n == 0)
		return (NULL);
	if (s1[i] == '\0' && s2[j] == '\0')
		return ((char*)s1);
	while (s1[i] && n)
	{
		if (n < ft_strlen(s2))
			return (NULL);
		if (ft_strncmp(s1 + i, s2, (ft_strlen(s2))) == 0)
			return ((char*)s1 + i);
		n--;
		i++;
	}
	return (NULL);
}
