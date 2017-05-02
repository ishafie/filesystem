/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:34:54 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/15 11:32:02 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	if (lst == NULL || f == NULL)
		return ;
	while (lst->next)
	{
		(*f)(lst);
		lst = lst->next;
	}
	(*f)(lst);
}
