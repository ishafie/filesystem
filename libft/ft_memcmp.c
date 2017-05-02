/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/25 15:56:43 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 17:54:16 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	*str2;
	int				cmp;

	str = (unsigned char*)s1;
	str2 = (unsigned char*)s2;
	i = -1;
	while (++i < n)
	{
		cmp = str[i] - str2[i];
		if (cmp != 0)
			return (cmp);
	}
	return (0);
}
