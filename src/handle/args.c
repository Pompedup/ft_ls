/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:58:06 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/07 13:54:09 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

time_t	get_time(char *link)
{
	t_stat	buf;

	if (!stat(link, &buf))
		return (buf.st_mtimespec.tv_sec);
	return (0);
}

int	is_dir(t_data *data, t_folder **folders, char *link, t_bool force)
{
	DIR			*dir;
	t_folder	*new;

	if (!(dir = opendir(link)) && !force)
		return (0);
	new_t_folder(&new, ft_strdup(link), dir);
	if (!new)
		return (-1);
	if (data->options & OPTION_T)
		new->time = get_time(link);
	sort_folders(data, folders, new);
	return (dir != NULL);
}

int	is_file(t_data *data, char *link)
{
	size_t		len;
	time_t		time;
	t_file	*new;

	if (!(time = get_time(link)))
		return (0);
	if (!data->files)
		new_t_folder(&data->files, NULL, NULL);
	new_t_file(&new, ft_strdup(link));
	if (!new)
		return (-1);
	if (!(get_data(data, link, new, data->files)))
		return (-1);
	if ((len = ft_strlen(link)) > data->files->len_max)
		data->files->len_max = len;
	data->files->nb_files++;
	if (data->options & OPTION_T)
		new->time = time;
	sort_files(data, &data->files->files, new);
	return (1);
}

t_bool	test_link(t_data *data, char *link)
{
	int ret;
	//-l readlink endby/
	if (!(ret = is_dir(data, &data->folders, link, FALSE)))
		if (!(ret = is_file(data, link)))
			new_t_error(&data->errors, link);
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
