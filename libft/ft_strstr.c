/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 12:40:46 by rle-mino          #+#    #+#             */
/*   Updated: 2015/11/30 20:39:41 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strstr(const char *s1, const char *s2)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s1[i] == '\0' && s2[j] == '\0')
		return ((char*)s1);
	while (s1[i])
	{
		if (ft_strncmp(s1 + i, s2, ft_strlen(s2)) == 0)
			return ((char *)s1 + i);
		i++;
	}
	return (NULL);
}
