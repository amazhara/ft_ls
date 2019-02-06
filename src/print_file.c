/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:42:37 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/06 21:24:54 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		ar_sort(t_argv **arr, int last)
{
	int		i;

	i = -1;
	while (++i < last)
		ft_swap((void**)arr + i, (void**)arr + last--);
}

void		abubb_sort(t_argv **arr)
{
	int		i;
	int		to_stop;

	i = -1;
	to_stop = 0;
	while (arr[++i])
	{
		if (arr[i + 1] && ft_strcmp(arr[i]->arg, arr[i + 1]->arg) > 0)
		{
			++to_stop;
			ft_swap((void**)arr + i, (void**)arr + i + 1);
		}
		if (*(arr + i + 1) == NULL && to_stop > 0)
		{
			to_stop = 0;
			i = -1;
		}
	}
}

void		atime_sort(t_argv **arr)
{
	int		i;
	int		to_stop;

	i = -1;
	to_stop = 0;
	while (arr[++i])
	{
		if (arr[i + 1] && arr[i]->stime < arr[i + 1]->stime)
		{
			++to_stop;
			ft_swap((void**)arr + i, (void**)arr + i + 1);
		}
		if (*(arr + i + 1) == NULL && to_stop > 0)
		{
			to_stop = 0;
			i = -1;
		}
	}
}

static int	count_files(t_argv *av)
{
	int		count;
	t_argv	*tmp;

	count = 0;
	tmp = av;
	while (tmp)
	{
		++count;
		tmp = tmp->next;
	}
	return (count);
}

void		check_file(t_ft_ls *ms)
{
	int		len;
	int		last;
	t_argv	*tmp;
	t_argv	**arr;

	take_atime(ms->av);
	len = count_files(ms->av);
	arr = (t_argv**)ft_memalloc(sizeof(t_argv*) * (len + 1));
	tmp = ms->av;
	last = len - 1;
	while (tmp)
	{
		arr[--len] = tmp;
		tmp = tmp->next;
	}
	ms->fl.t ? atime_sort(arr) : abubb_sort(arr);
	if (ms->fl.r)
		ar_sort(arr, last);
	ar_print(&ms->fl, arr);
	ms->arr = arr;
}
