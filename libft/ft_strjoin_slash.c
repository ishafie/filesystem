/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_slash.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/26 19:26:11 by ishafie           #+#    #+#             */
/*   Updated: 2016/03/25 17:39:33 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoin_slash(char const *s1, char const *s2)
{
	char	*fraiche;
	size_t	i;
	size_t	id;

	id = 0;
	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(fraiche = (char*)malloc(sizeof(char) * (ft_strlen(s1) +
		ft_strlen(s2)) + 2)))
		return (NULL);
	while (s1[i] != '\0')
	{
		fraiche[i] = s1[i];
		i++;
	}
	fraiche[i++] = '/';
	while (s2[id] != '\0')
	{
		fraiche[i] = s2[id];
		i++;
		id++;
	}
	fraiche[i] = '\0';
	return (fraiche);
}
