/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_dirs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:24:18 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 19:36:58 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	open_file(t_data *data, char *name)
{
	t_bool		exec;
	t_bool		dir;

	if (!(is_exec(NULL, name, &dir, &exec)))
		return (FALSE);
	if (!data->files)
		new_t_folder(&data->files, NULL);
	sort_files(&data->files->files, name, dir, exec);
	return (TRUE);
}

void	open_dirs(t_data *data, int ac, char **av)
{
	int			i;
	DIR			*dir;
	t_folder	**folder;

	i = 0;
	folder = &(data->folders);
	while (i < ac)
	{
		if ((dir = opendir(av[i])))
		{
			new_t_folder(folder, av[i]);
			folder = &((*folder)->next);
		}
		else if (!open_file(data, av[i]))
			new_t_error(&data->errors, av[i]);
		i++;
	}
}
