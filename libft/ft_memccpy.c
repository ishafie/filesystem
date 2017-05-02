/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 16:49:08 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/03 17:33:43 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	i = 0;
	d = (unsigned char *)dst;
	if (c < 0)
		c = ft_abs(c);
	s = (unsigned char *)src;
	while (i < n)
	{
		d[i] = s[i];
		if (s[i] == c)
			return (&d[i + 1]);
		i++;
	}
	return (NULL);
}
