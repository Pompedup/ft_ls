/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:30:42 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/07 16:27:43 by abezanni         ###   ########.fr       */
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

static char		*get_uid(t_stat *buf, t_folder *folder)
{
	struct passwd	*uid;
	size_t			len;

	if (!(uid = getpwuid(buf->st_uid)))
		return (ft_ulltoa_base(buf->st_uid, 10, FALSE));
	if (folder->uid_len < (len = ft_strlen(uid->pw_name)))
		folder->uid_len = len;
	return (ft_strdup(uid->pw_name));
}

t_bool	get_buf(char *link, t_stat *buf)
{
	if (lstat(link, buf) == -1)
		return (FALSE);
	return (TRUE);
	// if (stat(link, &buf) == -1)
}

time_t	get_sort_time(int options, t_stat *buf)
{
	if (options & OPTION_T)
	{
		if (options & OPTION_U)
			return (buf->st_atimespec.tv_sec);
		else if (options & OPTION_BIGU)
			return (buf->st_ctimespec.tv_sec);
	}
	return (buf->st_mtimespec.tv_sec);

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
		if (i == 0 && mode & S_ISVTX)
			rights[8 - i] = 't';
		i++;
	}
	return (rights);
}

t_bool	get_data(t_data *data, char *link, t_file *new, t_folder *folder)
{
	t_stat	buf;
	size_t	len;

	if (!get_buf(new->link, &buf))
		return (FALSE);
	if (!(new->name = ft_strdup(link)))
		return (FALSE);
	new->type = get_type(buf.st_mode);
	if (!(new->rights = get_rights(buf.st_mode)))
		return (FALSE);
	if (data->options & (OPTION_L | OPTION_T))
		new->time = get_sort_time(data->options, &buf);
	if (data->options & (OPTION_L))
	{
		folder->blocks += buf.st_blocks;
		new->nb_links = buf.st_nlink;
		if (folder->link_len < (len = ft_nbr_len(buf.st_nlink)))
			folder->link_len = len;
		new->size = buf.st_size;
		if (folder->size_len < (len = ft_nbr_len(buf.st_size)))
			folder->size_len = len;
		if (!(new->uid = get_uid(&buf, folder)))
			return (FALSE);
		if (!(get_option_l(&buf, new, folder)))
			return (FALSE);
	}
	return (TRUE);
}
