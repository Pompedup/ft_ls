/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/07 13:58:44 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/07 15:05:12 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int	add_dir(t_data *data, t_folder **folders, char *link, time_t time)
{
	DIR			*dir;
	t_folder	*new;

	ft_printf("%s - parse in dir\n", link);
	dir = opendir(link);
	new_t_folder(&new, ft_strdup(link), dir);
	if (!new)
		return (-1);
	new->time = time;
	sort_folders(data, folders, new);
	return (dir != NULL);
}

t_bool	link_dir(char *link, int options)
{
	t_stat	buf;

	if (stat(link, &buf))
	{
		if (S_ISDIR(buf.st_mode))
		{
			if (options & OPTION_L)
			{
				if (link[ft_strlen(link) - 1] != '/')
					return (FALSE);
			}
			return (TRUE);
		}
	}
	return (FALSE);
}

int		is_existing(t_data *data, char *link)
{
	t_stat	buf;

	if (!(lstat(link, &buf)))
		return (0);
	if (S_ISDIR(buf.st_mode) || (S_ISLNK(buf.st_mode) && link_dir(link, data->options)))
		return (add_dir(data, &data->folders, link, buf.st_mtimespec.tv_sec));
	ft_printf("%s - parse in file\n", link);
}

t_bool	test_link(t_data *data, char *link)
{
	int ret;

	if ((ret = is_existing(data, link)) == 0)
		new_t_error(&data->unknow, link);
	return (ret != -1);
}

t_bool	args(t_data *data, int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		if (!(test_link(data, av[i++])))
			return (FALSE);
	}
	return (TRUE);
}
