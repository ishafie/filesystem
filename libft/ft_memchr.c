/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:14:26 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/03 17:33:38 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	int				i;
	unsigned char	*str;

	str = (unsigned char*)s;
	i = 0;
	while (n)
	{
		if (str[i] == (unsigned char)c)
			return ((unsigned char*)s + i);
		i++;
		n--;
	}
	return (NULL);
}
