/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:02:15 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/03 17:34:05 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list		*tmp;
	t_list		*a;

	tmp = (*alst);
	while (tmp)
	{
		a = tmp->next;
		(*del)(tmp->content, tmp->content_size);
		free(tmp);
		tmp = a;
	}
	(*alst) = NULL;
}
