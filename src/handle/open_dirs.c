/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:24:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 18:18:49 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	open_file(t_data *data, char *name)
{
	t_file	*new;
	t_stat	buf;

	if (!(get_stats(NULL, name, &buf)))
		return (FALSE);
	if (!data->files)
		new_t_folder(&data->files, NULL, NULL);
	new_t_file(&new, name);
	new->type = (buf.st_mode & S_IFDIR) != 0;
	new->exec = (buf.st_mode & 73) != 0;
	if (data->options & OPTION_T)
	{
		new->time = buf.st_mtimespec.tv_sec;
		new->size = buf.st_size;
		sort_files_by_time(&data->files->files, new);
	}
	else
		sort_files_by_name(&data->files->files, new);
	return (TRUE);
}

void	open_dirs(t_data *data, int ac, char **av)
{
	int			i;
	DIR			*dir;
	t_folder	**folder;
	t_folder	*new;
	t_stat		buf;

	i = 0;
	folder = &(data->folders);
	while (i < ac)
	{
		if ((dir = opendir(av[i])))
		{
			new_t_folder(&new, ft_strdup(av[i]), dir);
			if (data->options & OPTION_T)
			{
				get_stats(NULL, new->name, &buf);
				new->time = buf.st_mtimespec.tv_sec;
				new->size = buf.st_size;
				sort_folders_by_time(folder, new);
			}
			else
				sort_folders_by_name(folder, new);
		}
		else if (!open_file(data, av[i]))
			new_t_error(&data->errors, av[i]);
		i++;
	}
}
