/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 21:37:21 by amazhara          #+#    #+#             */
/*   Updated: 2018/11/04 13:22:32 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*newl;
	t_list	*start;

	if (!lst || !f)
		return (NULL);
	newl = f(lst);
	start = newl;
	while (lst->next)
	{
		lst = lst->next;
		if (!(newl->next = f(lst)))
			return (NULL);
		newl = newl->next;
	}
	return (start);
}
