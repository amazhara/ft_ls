/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 17:21:22 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/06 21:34:12 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LS_H
# define _FT_LS_H

# include <sys/stat.h>
# include <errno.h>
# include <stdio.h>
# include <dirent.h>
# include <pwd.h>
# include <time.h>
# include <sys/acl.h>
# include <grp.h>
# include <sys/xattr.h>
# include "../printf/libftprintf.h"

typedef struct s_ft_ls		t_ft_ls;
typedef struct s_ftmp		t_ftmp;
typedef struct s_files_stat	t_files;
typedef struct s_ls_flags	t_flags;
typedef struct s_ls_argv	t_argv;

struct	s_files_stat
{
	int			fold;
	char		*name;
	char		*time;
	char		*gid;
	char		*uid;
	char		*xattr;
	char		*link;
	uint		nlinks;
	uint		stime;
	uint		sort_time;
	intmax_t	size;
	t_files		*next;
};

struct	s_ls_flags
{
	size_t			l;
	size_t			a;
	size_t			t;
	uint			rr;
	size_t			u;
	size_t			x;
	intmax_t		r;
};

struct	s_ftmp
{
	t_argv	*fsave;
	t_ftmp	*fnext;
};

struct	s_ls_argv
{
	int			first	: 1;
	int			is_file	: 1;
	int			last;
	char		*arg;
	uint		stime;
	t_ftmp		*flist;
	t_files		*files;
	t_argv		*next;
	t_files		**output;
	intmax_t	total;
};

struct	s_ft_ls
{
	t_flags		fl;
	t_argv		*av;
	t_argv		**arr;
};

int		pars_flags(t_ft_ls *ms, char **argv);
void	plenum_flist(t_ft_ls *ms, t_argv *argm);
void	bubble_sort(t_argv *argm, int timeflag);
void	classic_ls_output(t_flags *fl, t_argv *av);
void	r_sort(t_files **arr, int last);
void	ls_out(t_argv av, int flag);
void	arf_info(t_argv *argm);
void	check_file(t_ft_ls *ms);
void	take_atime(t_argv *av);
void	ar_print(t_flags *fl, t_argv **arr);
void	ls_output(t_flags *fl, t_argv *av);
void	d_inf(t_files *tmp, char *tmp_way, struct stat sbuf);

#endif
