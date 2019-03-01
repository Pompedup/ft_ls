/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:36:23 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/01 17:57:27 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void	new_folder()
// {
	//
// }

char	*create_name(char *name, char *end)
{
	int		i;
	char	*back;

	i = ft_strlen(name) - 1;
	if (name[i] != '/')
	{
		back = ft_strjoin(name, "/");
		return (ft_strmjoin(back, end, 1));
	}
	return (ft_strjoin(name, end));
}

void	sort_folders_by_time(t_folder **folders, t_folder *new)
{
	while (*folders)
	{
		folders = &((*folders)->next);
	}
	new->next = *folders;
	*folders = new;
}

void	sort_folders_by_name(t_folder **folders, t_folder *new)
{
	while (*folders)
	{
		if (ft_strcmp(new->name, (*folders)->name) < 0)
		{
			new->next = *folders;
			*folders = new;
			return ;
		}
		folders = &((*folders)->next);
	}
	new->next = *folders;
	*folders = new;
}

void	handle_folder(t_data *data, t_folder *folder)
{
	closedir(folder->dir);
	handle_folders(data, folder->subfolders);
}

void	handle_folders(t_data *data, t_folder *folders)
{
	t_folder *next;

	while (folders)
	{
		next = folders->next;
		handle_folder(data, folders);
		folders = next;
	}
}


// void	recursive(t_data *data, char *link)
// {
// 	t_folder	*folder;
// 	t_bool		dir;
// 	t_bool		exec;

// 	new_t_folder(&folder, link);
// 	folder->dir = opendir(link);
// 	while ((folder->file = readdir(folder->dir)))
// 	{
// 		if (*folder->file->d_name != '.')
// 		{
// 			is_exec(link, folder->file->d_name, &dir, &exec);
// 			handle_folder(folder, folder->file->d_namlen);
// 			sort_files(&folder->files, folder->file->d_name, folder->file->d_type == 4, exec);
// 		}
// 	}
// //	aff(folder);
// }
