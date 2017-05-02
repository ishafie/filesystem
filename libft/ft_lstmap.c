/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rle-mino <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/02 17:54:48 by rle-mino          #+#    #+#             */
/*   Updated: 2015/12/03 17:33:53 by rle-mino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list			*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list		*nm;
	t_list		*t1;
	t_list		*t2;

	if (!lst || !f)
		return (NULL);
	t2 = (f)(lst);
	if ((nm = ft_lstnew(t2->content, t2->content_size)))
	{
		t1 = nm;
		lst = lst->next;
		while (lst)
		{
			t2 = (f)(lst);
			if (!(t1->next = ft_lstnew(t2->content, t2->content_size)))
				return (NULL);
			t1 = t1->next;
			lst = lst->next;
		}
	}
	return (nm);
}
