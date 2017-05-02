/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:47:41 by rle-mino          #+#    #+#             */
/*   Updated: 2016/05/15 03:16:04 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*s2;
	size_t	i;

	i = 0;
	if (s == NULL)
		return (NULL);
	if (!(s2 = (char*)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len && s[start])
		s2[i++] = s[start++];
	s2[i] = '\0';
	return (s2);
}
