/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:19:12 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/06 21:11:59 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	start_algorithm(t_ft_ls *ms)
{
	int		i;

	i = -1;
	while (ms->arr[++i])
	{
		if (!ms->arr[i]->is_file)
			plenum_flist(ms, ms->arr[i]);
	}
}

int		main(int argc, char *argv[])
{
	t_ft_ls	ms;

	ft_bzero(&ms, sizeof(t_ft_ls));
	(void)argc;
	ms.av = (t_argv *)ft_memalloc(sizeof(t_argv));
	if (pars_flags(&ms, argv) < 0)
	{
		ft_printf("ft_ls: %s", "illegal option");
		return (0);
	}
	check_file(&ms);
	if (ms.av->arg)
		start_algorithm(&ms);
}
