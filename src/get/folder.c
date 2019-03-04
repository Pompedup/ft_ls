/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:26:47 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/04 16:01:26 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

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

#include <stdio.h>

static t_bool	handle_folder(t_data *data, t_folder **folder)
{
	t_dirent	*dirent;
	t_file		*file;

	while ((*folder)->dir && (dirent = readdir((*folder)->dir)))
	{
		if ((data->options & OPTION_A || *dirent->d_name != '.')
			|| (data->options & OPTION_BIGA &&\
			(ft_strcmp(".", dirent->d_name) && ft_strcmp("..", dirent->d_name))))
		{
			if (!(file = add_file((*folder)->name, dirent->d_name)))
				return (FALSE);
			if (!(get_data(data, dirent->d_name, file, *folder)))
				return (FALSE);
			sort_files(data, &(*folder)->files, file);
			if (dirent->d_namlen > (*folder)->len_max)
				(*folder)->len_max = dirent->d_namlen;
			// perror("here : ");//ft_fprintf(2, "ERROR\n");
			(*folder)->nb_files++;
		}
	}
	display_folder(data, *folder);
	data->print_name = TRUE;
	if ((*folder)->dir)
		closedir((*folder)->dir);
	(*folder)->dir = NULL;
	while ((*folder)->subfolders)
		handle_folder(data, &(*folder)->subfolders);
	del_t_folder(folder);
	return (TRUE);
}

t_bool	get_folders(t_data *data, t_folder **folders)
{
	while (*folders)
	{
		if (!(handle_folder(data, folders)))
			return (FALSE);
	}
	return (TRUE);
}
