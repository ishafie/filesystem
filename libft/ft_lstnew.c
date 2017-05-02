/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/03 15:02:12 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/08 15:23:45 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstnew(void const *content, size_t content_size)
{
	t_list		*nm;

	nm = (t_list*)malloc(sizeof(t_list));
	if (!(nm))
		return (NULL);
	if (content)
	{
		nm->content = malloc(content_size);
		if (!(nm->content))
			return (NULL);
		nm->content = ft_memcpy(nm->content, content, content_size);
		nm->content_size = content_size;
	}
	else
	{
		nm->content = NULL;
		nm->content_size = 0;
	}
	nm->next = NULL;
	return (nm);
}
