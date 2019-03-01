/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 14:58:06 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/01 19:13:04 by abezanni         ###   ########.fr       */
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

t_bool	is_dir(t_data *data, char *link)
{
	DIR			*dir;
	t_container	*new;

	if (!(dir = opendir(link)))
		return (FALSE);
	new_t_container(&new, ft_strdup(link), dir);
	if (data->options & OPTION_T)
	{
		new->time = get_time(link);
		container_by_time(data, &data->container_dir, new);
	}
	else
		container_by_name(data, &data->container_dir, new);
	return (TRUE);
}

t_bool	is_file(t_data *data, char *link)
{
	size_t		len;
	time_t		time;
	t_container	*new;

	if (!(time = get_time(link)))
		return (FALSE);
	new_t_container(&new, ft_strdup(link), NULL);
	if ((len = ft_strlen(link)) > data->max_lenght)
		data->max_lenght = len + 1;
	data->nb_files++;
	if (data->options & OPTION_T)
	{
		new->time = time;
		container_by_time(data, &data->container_files, new);
	}
	else
		container_by_name(data, &data->container_files, new);
	return (TRUE);
}

void	test_link(t_data *data, char *link)
{
	if (!is_dir(data, link))
		if (!is_file(data, link))
			new_t_error(&data->errors, link);
}

void	args(t_data *data, int ac, char **av)
{
	int i;

	i = 0;
	while (i < ac)
		test_link(data, av[i++]);
}
