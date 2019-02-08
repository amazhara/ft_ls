/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plenum_flist.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 09:16:09 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/08 15:25:23 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#define FNAME dninf->d_name

static void		take_more_fold(t_argv *argm)
{
	int			i;
	t_ftmp		*ftmp;
	char		*tmp_way;
	char		*case_leak;
	struct stat	sbuf;

	i = -1;
	argm->flist = (t_ftmp*)ft_memalloc(sizeof(t_ftmp));
	ftmp = argm->flist;
	while (argm->output[++i])
	{
		case_leak = ft_strjoin(argm->arg, "/");
		tmp_way = ft_strjoin(case_leak, argm->output[i]->name);
		ft_strdel(&case_leak);
		lstat(tmp_way, &sbuf);
		if (S_ISDIR(sbuf.st_mode) && ft_strcmp(argm->output[i]->name, ".")
		&& ft_strcmp(argm->output[i]->name, ".."))
		{
			ftmp->fsave = (t_argv*)ft_memalloc(sizeof(t_argv));
			ftmp->fsave->arg = ft_strdup(tmp_way);
			ftmp->fnext = (t_ftmp*)ft_memalloc(sizeof(t_ftmp));
			ftmp = ftmp->fnext;
		}
		ft_strdel(&tmp_way);
	}
}

static void		take_dinfo(t_argv *argm)
{
	t_files		*tmp;
	char		*tmp_way;
	char		*case_leak;
	struct stat	sbuf;
	intmax_t	blocks;

	tmp = argm->files;
	blocks = 0;
	while (tmp)
	{
		case_leak = ft_strjoin(argm->arg, "/");
		tmp_way = ft_strjoin(case_leak, tmp->name);
		lstat(tmp_way, &sbuf);
		if (sbuf.st_mode)
		{
			d_inf(tmp, tmp_way, sbuf);
			blocks += sbuf.st_blocks;
		}
		ft_strdel(&case_leak);
		ft_strdel(&tmp_way);
		tmp = tmp->next;
	}
	argm->total = blocks;
}

static void		recurs_ls(t_ft_ls *ms, t_argv *argm)
{
	t_ftmp			*av;

	bubble_sort(argm, ms->fl.t);
	if (ms->fl.r)
		r_sort(argm->output, argm->last);
	if (ms->fl.rr && argm->files->name)
		take_more_fold(argm);
	ls_out(*argm, ms->fl.l);
	av = argm->flist;
	while (ms->fl.rr && argm->flist && argm->flist->fsave)
	{
		plenum_flist(ms, argm->flist->fsave);
		argm->flist = argm->flist->fnext;
	}
	argm->flist = av;
}

void			plenum_flist(t_ft_ls *ms, t_argv *argm)
{
	DIR				*dir;
	t_files			*tmp;
	struct dirent	*dninf;

	argm->files = (t_files *)ft_memalloc(sizeof(t_files));
	tmp = argm->files;
	dir = opendir(argm->arg);
	if (dir)
		while ((dninf = readdir(dir)))
			if ((FNAME[0] == '.' && ms->fl.a) || FNAME[0] != '.')
			{
				if (tmp->name)
				{
					tmp->next = (t_files*)ft_memalloc(sizeof(t_files));
					tmp = tmp->next;
				}
				tmp->name = ft_strdup(FNAME);
			}
	if (dir)
		closedir(dir);
	else
		check_arg(argm->arg);
	if (argm->files->name)
		take_dinfo(argm);
	recurs_ls(ms, argm);
}
