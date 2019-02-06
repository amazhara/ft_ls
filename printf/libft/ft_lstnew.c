/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/03 17:19:57 by amazhara          #+#    #+#             */
/*   Updated: 2018/11/03 19:10:07 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*point;

	if (!(point = (t_list *)malloc(sizeof(t_list))))
		return (NULL);
	if (!content)
	{
		point->content = NULL;
		point->content_size = 0;
		point->next = NULL;
		return (point);
	}
	else
	{
		if (!(point->content = malloc(content_size)))
		{
			free(point);
			return (NULL);
		}
		ft_memcpy(point->content, content, content_size);
		point->content_size = content_size;
	}
	point->next = NULL;
	return (point);
}
