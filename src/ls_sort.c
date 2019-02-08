/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_sort.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 13:32:15 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/08 15:29:06 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	r_sort(t_files **arr, int last)
{
	int		i;

	i = -1;
	while (++i < last)
		ft_swap((void**)arr + i, (void**)arr + last--);
}

int		count_files_len(t_files *files)
{
	t_files	*tmp;
	int		count;

	count = 0;
	tmp = files;
	while (tmp)
	{
		++count;
		tmp = tmp->next;
	}
	return (count);
}

void	time_bsort(t_files **arr)
{
	int		i;
	int		to_stop;

	i = -1;
	to_stop = 0;
	while (arr[++i])
	{
		if (arr[i + 1] && arr[i]->sort_time < arr[i + 1]->sort_time)
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

void	classic_bsort(t_files **arr)
{
	int		i;
	int		to_stop;

	i = -1;
	to_stop = 0;
	while (arr[++i])
	{
		if (arr[i + 1] && ft_strcmp(arr[i]->name, arr[i + 1]->name) > 0)
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

void	bubble_sort(t_argv *argm, int timeflag)
{
	t_files	**arr;
	t_files	*tmp;
	int		len;

	len = count_files_len(argm->files);
	tmp = argm->files;
	arr = (t_files **)malloc(sizeof(t_files *) * (len + 1));
	arr[len] = NULL;
	len = 0;
	while (tmp)
	{
		arr[len++] = tmp;
		tmp = tmp->next;
	}
	argm->last = len - 1;
	classic_bsort(arr);
	if (timeflag)
		time_bsort(arr);
	argm->output = arr;
}
