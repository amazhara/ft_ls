/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_output.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 12:13:22 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/08 15:41:53 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static inline t_flags	sort_output(t_argv *av)
{
	t_files	*tmp;
	t_flags	fl;

	tmp = av->files;
	ft_bzero(&fl, sizeof(fl));
	while (tmp)
	{
		ft_strlen(tmp->name) > fl.l ? fl.l = ft_strlen(tmp->name) : 0;
		ft_strlen(tmp->time) > fl.a ? fl.a = ft_strlen(tmp->time) : 0;
		ft_strlen(tmp->gid) > fl.t ? fl.t = ft_strlen(tmp->gid) : 0;
		ft_strlen(tmp->uid) > fl.u ? fl.u = ft_strlen(tmp->uid) : 0;
		ft_strlen(tmp->xattr) > fl.x ? fl.x = ft_strlen(tmp->xattr) : 0;
		ft_intlen(tmp->size) > fl.r ? fl.r = ft_intlen(tmp->size) : 0;
		ft_intlen(tmp->nlinks) > fl.rr ? fl.rr = ft_intlen(tmp->nlinks) : 0;
		tmp = tmp->next;
	}
	return (fl);
}

static inline void		ls_print(t_files *s, int mode, char *link)
{
	if (mode == 1)
	{
		if (link)
			ft_printf("%11s%4u %8s %5s %6jd %s %s -> %s\n", s->xattr, s->nlinks,
			s->uid, s->gid, s->size, s->time, s->name, s->link);
		else
			ft_printf("%11s%4u %8s %5s%6jd %s %s\n", s->xattr, s->nlinks,
			s->uid, s->gid, s->size, s->time, s->name);
	}
	else
		ft_printf("%s\n", s->name);
}

static inline void		ls_good_print(t_files *s, char *link, t_flags fl)
{
	if (link)
		ft_printf("%*s %*u %-*s  %-*s  %*jd %-*s %s -> %s\n", fl.x, s->xattr,
		fl.rr, s->nlinks, fl.u, s->uid, fl.t, s->gid, fl.r, s->size, fl.a,
		s->time, s->name, s->link);
	else
		ft_printf("%*s %*u %-*s  %-*s  %*jd %-*s %s\n", fl.x, s->xattr,
		fl.rr, s->nlinks, fl.u, s->uid, fl.t, s->gid, fl.r, s->size, fl.a,
		s->time, s->name);
}

void					ls_out(t_argv av, int flag)
{
	int		i;
	t_flags	fl;

	i = -1;
	if (!av.first)
		write(1, "\n", 1);
	if (!av.first || (av.first && av.next))
		ft_printf("%s:\n", av.arg);
	if (av.output[0]->name)
	{
		if (flag)
			ft_printf("total %d\n", av.total);
		if (flag)
			fl = sort_output(&av);
		while (av.output[++i])
		{
			if (!flag)
				ls_print(av.output[i], flag, av.output[i]->link);
			else
				ls_good_print(av.output[i], av.output[i]->link, fl);
		}
	}
}

void					ar_print(t_flags *fl, t_argv **arr)
{
	int		i;

	i = -1;
	while (arr[++i])
		if (arr[i]->is_file)
		{
			arr[i]->files = (t_files*)ft_memalloc(sizeof(t_files));
			if (fl->l)
				arf_info(arr[i]);
			arr[i]->files->name = ft_strdup(arr[i]->arg);
			ls_print(arr[i]->files, fl->l, arr[i]->files->link);
		}
}
