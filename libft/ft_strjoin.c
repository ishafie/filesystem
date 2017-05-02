/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ishafie <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 21:50:07 by ishafie           #+#    #+#             */
/*   Updated: 2016/04/26 21:50:07 by ishafie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	int		i;
	int		k;

	i = 0;
	k = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(s3 = (char*)ft_memalloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	while (s1[i])
		s3[k++] = s1[i++];
	i = 0;
	while (s2[i])
		s3[k++] = s2[i++];
	return (s3);
}
