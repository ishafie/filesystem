/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/28 13:27:12 by rle-mino          #+#    #+#             */
/*   Updated: 2016/04/24 18:02:49 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*s2;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	i = -1;
	if (!(s2 = ft_strnew(ft_strlen(s))))
		return (NULL);
	while (s[++i])
		s2[i] = f(i, s[i]);
	return (s2);
}
