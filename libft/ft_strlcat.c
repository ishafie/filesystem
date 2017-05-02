/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 10:24:34 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 18:01:49 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;
	size_t		a;

	j = 0;
	i = 0;
	while (i < size && dst[i])
		i++;
	a = i;
	while (i < (size - 1) && src[j])
		dst[i++] = src[j++];
	if (size > a)
		dst[i] = '\0';
	return (ft_strlen(src) + a);
}
