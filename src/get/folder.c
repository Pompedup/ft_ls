/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:26:47 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/02 19:24:54 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		get_type(mode_t mode)
{
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISFIFO(mode))
		return ('f');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISREG(mode))
		return ('-');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISWHT(mode))
		return ('w');
	return ('?');
}

static char		get_signe(size_t i)
{
	if (i % 3 == 2)
		return ('r');
	else if (i % 3 == 1)
		return ('w');
	return ('x');
}

static char		*get_rights(mode_t mode)
{
	char	*rights;
	size_t	i;

	i = 0;
	if (!(rights = ft_strnew(10)))
		return (NULL);
	while (i < 9)
	{
		if (1 << i & mode)
			rights[8 - i] = get_signe(i);
		else
			rights[8 - i] = '-';
		i++;
	}
	return (rights);
}

static char		*get_uid(t_stat *buf, t_folder *folder)
{
	struct passwd	*uid;
	size_t			len;

	if (!(uid = getpwuid(buf->st_uid)))
		return (NULL);
	if (folder->uid_len < (len = ft_strlen(uid->pw_name)))
		folder->uid_len = len;
	return (ft_strdup(uid->pw_name));
}

static char		*get_gid(t_stat *buf, t_folder *folder)
{
	struct group	*gid;
	size_t			len;

	if (!(gid = getgrgid(buf->st_gid)))
		return (NULL);
	if (folder->gid_len < (len = ft_strlen(gid->gr_name)))
		folder->gid_len = len;
	return (ft_strdup(gid->gr_name));
}

static char		*get_sym_link(char *link)
{
	char	buf[256];
	int		ret;

	// ft_printf("%s\n");
	if ((ret = readlink(link, buf, 255)) == -1)
		return (NULL);
	buf[ret] = '\0';
	return (ft_strdup(buf));
}

static t_bool	get_data(t_data *data, char *link, t_file *new, t_folder *folder)
{
	t_stat	buf;
	size_t	len;

	// if (stat(link, &buf) == -1)
	if (lstat(new->link, &buf) == -1)
		return (FALSE);
	// new_t_file(&new, link);
	if (data->options & (OPTION_L | OPTION_T))
		new->time = buf.st_mtimespec.tv_sec;
	if (data->options & (OPTION_L))
	{
		new->name = ft_strdup(link);
		new->type = get_type(buf.st_mode);
		new->rights = get_rights(buf.st_mode);
		new->nb_links = buf.st_nlink;
		if (folder->link_len < (len = ft_nbr_len(buf.st_nlink)))
			folder->link_len = len;
		new->uid = get_uid(&buf, folder);
		new->gid = get_gid(&buf, folder);
		new->size = buf.st_size;
		if (new->type == 'l')
			new->sym_link = get_sym_link(new->link);
	}
	return (TRUE);
}

t_file			*add_file(char *folder, char *name)
{
	t_file	*new;
	char	*link;

	ft_sprintf(&link, "%s/%s", folder, name);
	if (!link)
		return (NULL);
	new_t_file(&new, link);
	return (new);
}

static t_bool	handle_folder(t_data *data, t_folder *folder)
{
	t_dirent	*dirent;
	t_file		*file;

//	if (data->options & OPTION_BIGR)
		//do recursion
	while ((dirent = readdir(folder->dir)))
	{
		if (data->options & OPTION_A || *dirent->d_name != '.')
		{
			if (!(file = add_file(folder->name, dirent->d_name)))
				return (FALSE);
			if (!(get_data(data, dirent->d_name, file, folder)))
				return (FALSE);
			sort_files(data, &folder->files, file);
			if (dirent->d_namlen > folder->len_max)
				folder->len_max = dirent->d_namlen;
		}
		folder->nb_files++;
	}
	display_folder(data, folder);
	return (TRUE);
}

static t_bool	init_folder(t_data *data, t_container *contain)
{
	t_folder *folder;

	new_t_folder(&folder, contain->name, contain->dir);
	return (handle_folder(data, folder));
}

t_bool	get_folders(t_data *data, t_container **contains)
{
	while (*contains)
	{
		if (!(init_folder(data, *contains)))
			return (FALSE);
		del_t_container(contains);
	}
	return (TRUE);
}
