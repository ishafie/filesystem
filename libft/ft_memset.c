/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 16:51:56 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 17:55:27 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memset(void *b, int c, size_t len)
{
	size_t			j;
	unsigned char	*d;

	d = (unsigned char*)b;
	j = -1;
	while (++j < len)
		d[j] = c;
	return (d);
}
