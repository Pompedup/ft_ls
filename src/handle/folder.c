/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:36:23 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 18:43:21 by abezanni         ###   ########.fr       */
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
		if ((*folders)->time <= new->time)
		{
			if ((*folders)->time == new->time)
			{
				while (*folders && (*folders)->time == new->time)
				{
					if (ft_strcmp(new->name, (*folders)->name) < 0)
						break ;
					folders = &((*folders)->next);
				}
			}
			new->next = *folders;
			*folders = new;
			return ;
		}
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
	t_file		*new_file;
	t_folder	*new_folder;
	size_t		n;
	t_stat		buf;

	n = 0;
	while ((folder->file = readdir(folder->dir)))
	{
		if (*folder->file->d_name != '.' || data->options & OPTION_A)
		{
			if (folder->file->d_type == 4 && data->options & OPTION_BIGR)
			{
				if (ft_strcmp(".", folder->file->d_name) && ft_strcmp("..", folder->file->d_name))
				{
					new_t_folder(&new_folder, create_name(folder->name, folder->file->d_name), NULL);
					if (data->options & OPTION_T)
					{
						get_stats(NULL, new_folder->name, &buf);
						new_folder->time = buf.st_mtimespec.tv_sec;
						new_folder->size = buf.st_size;
						sort_folders_by_time(&folder->subfolders, new_folder);
					}
					else
						sort_folders_by_name(&folder->subfolders, new_folder);
					n++;
				}
			}
			get_stats(folder->name, folder->file->d_name, &buf);
			if (folder->len_max < folder->file->d_namlen)
				folder->len_max = folder->file->d_namlen;
			folder->nb_files++;
			new_t_file(&new_file, folder->file->d_name);
			new_file->type = (buf.st_mode & S_IFDIR) != 0;
			new_file->exec = (buf.st_mode & 73) != 0;
			if (data->options & OPTION_T)
			{
				new_file->time = buf.st_mtimespec.tv_sec;
				new_file->size = buf.st_size;
				sort_files_by_time(&folder->files, new_file);
			}
			else
				sort_files_by_name(&folder->files, new_file);
		}
	}
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
