/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 18:04:02 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/08 17:02:48 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int			check_arg(char *str)
{
	DIR				*dir;

	if (!(dir = opendir(str)))
	{
		if (!ft_strcmp(strerror(errno), strerror(ENOTDIR)))
			return (2);
		else
			ft_printf("ft_ls: %.*s: %s\n", ft_strlen(str),
			str, strerror(errno));
		return (1);
	}
	if (dir)
		closedir(dir);
	return (0);
}

static int	take_args(char **argv, t_argv *tmp_av, int j)
{
	int		i;
	int		c;

	i = j;
	while (argv[i])
	{
		c = check_arg(argv[i]);
		if (c == 1 && ++i)
			continue;
		if (tmp_av->arg)
		{
			tmp_av->next = (t_argv *)ft_memalloc(sizeof(t_argv));
			tmp_av = tmp_av->next;
		}
		tmp_av->arg = ft_strdup(argv[i++]);
		if (c == 2)
			tmp_av->is_file = true;
	}
	return (i);
}

static void	check_flag(char *str, t_flags *fl)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		str[i] == 'l' ? fl->l = 1 : 0;
		str[i] == 'a' ? fl->a = 1 : 0;
		str[i] == 't' ? fl->t = 1 : 0;
		str[i] == 'r' ? fl->r = 1 : 0;
		str[i] == 'R' ? fl->rr = 1 : 0;
	}
}

int			pars_flags(t_ft_ls *ms, char **argv)
{
	int		j;
	int		i;
	t_argv	*tmp_av;

	j = 0;
	tmp_av = ms->av;
	while (argv[++j])
	{
		if (argv[j][0] == '-')
		{
			if (argv[j][1] == '.')
				return (-1);
			check_flag(argv[j], &(ms->fl));
		}
		else
			break ;
	}
	i = take_args(argv, tmp_av, j);
	j == i ? tmp_av->arg = ft_strdup(".") : 0;
	j == i ? tmp_av->first = 1 : 0;
	j != i ? ms->av->first = 1 : 0;
	return (1);
}
