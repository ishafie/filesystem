/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/24 10:10:49 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 17:54:32 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*d;
	unsigned char		*s;
	size_t				i;

	i = -1;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (++i < n)
		d[i] = s[i];
	return (dst);
}
