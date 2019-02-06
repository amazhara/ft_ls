/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   take_inf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amazhara <amazhara@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:53:39 by amazhara          #+#    #+#             */
/*   Updated: 2019/02/06 21:27:02 by amazhara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void		arf_info(t_argv *argm)
{
	t_files		*tmp;
	struct stat	sbuf;

	tmp = argm->files;
	lstat(argm->arg, &sbuf);
	if (sbuf.st_mode != 16713)
		d_inf(tmp, argm->arg, sbuf);
}

void		take_atime(t_argv *av)
{
	t_argv		*tmp;
	struct stat	sbuf;

	tmp = av;
	while (tmp)
	{
		lstat(tmp->arg, &sbuf);
		if (sbuf.st_mode != 16713)
			tmp->stime = sbuf.st_ctimespec.tv_sec;
		tmp = tmp->next;
	}
}

static char	take_ftipe(mode_t st_mode)
{
	char	c;

	c = '-';
	c = (S_IFMT & st_mode) == S_IFDIR ? 'd' : c;
	c = (S_IFMT & st_mode) == S_IFIFO ? 'p' : c;
	c = (S_IFMT & st_mode) == S_IFCHR ? 'c' : c;
	c = (S_IFMT & st_mode) == S_IFBLK ? 'b' : c;
	c = (S_IFMT & st_mode) == S_IFLNK ? 'l' : c;
	c = (S_IFMT & st_mode) == S_IFSOCK ? 's' : c;
	return (c);
}

static char	*take_xattr(mode_t st_mode, char *passname)
{
	char	*str;
	size_t	xattr;
	acl_t	acl;

	acl = NULL;
	acl = acl_get_link_np(passname, ACL_TYPE_EXTENDED);
	str = (char*)ft_memalloc(sizeof(char) * 12);
	ft_memset(str, '-', 11);
	*str = take_ftipe(st_mode);
	*(str + 1) = (st_mode & S_IRUSR) ? 'r' : '-';
	*(str + 2) = (st_mode & S_IWUSR) ? 'w' : '-';
	*(str + 3) = (st_mode & S_IXUSR) ? 'x' : '-';
	*(str + 4) = (st_mode & S_IRGRP) ? 'r' : '-';
	*(str + 5) = (st_mode & S_IWGRP) ? 'w' : '-';
	*(str + 6) = (st_mode & S_IXGRP) ? 'x' : '-';
	*(str + 7) = (st_mode & S_IROTH) ? 'r' : '-';
	*(str + 8) = (st_mode & S_IWOTH) ? 'w' : '-';
	*(str + 9) = (st_mode & S_IXOTH) ? 'x' : '-';
	xattr = listxattr(passname, NULL, 0, XATTR_NOFOLLOW);
	str[10] = (xattr > 0) ? '@' : ' ';
	str[10] = acl ? '+' : str[10];
	free(acl);
	return (str);
}

void		d_inf(t_files *tmp, char *tmp_way, struct stat sbuf)
{
	tmp->time = ft_strsub(ctime(&sbuf.st_mtime), 4, 12);
	tmp->sort_time = sbuf.st_ctimespec.tv_sec;
	tmp->size = sbuf.st_size;
	tmp->gid = ft_strdup(getgrgid(sbuf.st_gid)->gr_name);
	tmp->uid = ft_strdup(getpwuid(sbuf.st_uid)->pw_name);
	tmp->link = ft_memalloc(sbuf.st_size + 1);
	if (ft_strcmp(tmp->name, ".") > 0 && ft_strcmp(tmp->name, "..") > 0)
		readlink(tmp_way, tmp->link, sbuf.st_size + 1);
	if (tmp->link[0] == '\0' || !tmp->link)
		ft_strdel(&tmp->link);
	tmp->nlinks = sbuf.st_nlink;
	tmp->xattr = take_xattr(sbuf.st_mode, tmp_way);
}
