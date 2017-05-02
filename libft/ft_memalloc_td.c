/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc_td.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 19:48:06 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/20 12:34:53 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_memalloc_td(int d1, int d2)
{
	char		**tab;
	char		*tab2;
	int			i;

	i = 0;
	tab = (char**)ft_memalloc(sizeof(char *) * d1);
	tab2 = (char*)ft_memalloc(sizeof(char) * d2 * d1);
	while (i < d1)
	{
		tab[i] = &tab2[i * d2];
		i++;
	}
	return (tab);
}
