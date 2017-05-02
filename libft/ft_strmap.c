/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 11:56:31 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 18:03:08 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strmap(char const *s, char (*f)(char))
{
	char	*s2;
	int		i;

	i = -1;
	if (s == NULL || f == NULL)
		return (NULL);
	if (!(s2 = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[++i])
		s2[i] = f(s[i]);
	return (s2);
}
