/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:58:06 by abezanni          #+#    #+#             */
/*   Updated: 2019/02/25 17:05:48 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_bool	open_file(t_data *data, char *name)
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

time_t	get_time(char *link)
{
	t_stat	buf;

	stat(link, &buf);
	return (buf.st_mtimespec.tv_sec);
}

t_bool	is_dir(t_data *data, char *link)
{
	DIR			*dir;
	t_container	*new;

	(void)data;
	if (!(dir = opendir(link)))
		return (FALSE);
	new_t_container(&new, ft_strdup(link), dir);
	if (data->options & OPTION_T)
	{
		new->time = get_time(link);
		container_by_time(data, &data->container, new);
	}
	else
		container_by_name(data, &data->container, new);
	return (TRUE);
}

t_bool	is_file(t_data *data, char *link)
{
	time_t		time;
	t_container	*new;

	if (!(time = get_time(link)))
		return (FALSE);
	new_t_container(&new, ft_strdup(link), NULL);



	return (TRUE);
	t_file	*new;
	t_stat	buf;

	if (!(get_stats(NULL, link, &buf)))
		return (FALSE);
	if (!data->files)
		new_t_folder(&data->files, NULL, NULL);
	new_t_file(&new, link);
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

void	test_link(t_data *data, char *link)
{
	if (!(is_dir(data, link) && is_file(data, link)))
		new_t_error(&data->errors, link);
}

void	args(t_data *data, int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
	{
		test_link(data, av[i++]);
		// test fichier dossier rien
	}
}
