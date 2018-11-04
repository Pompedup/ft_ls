/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:36:38 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 18:43:12 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

// void	sort_files_by_time(t_file **file, char *name, int)
// {
// 	while (*file)
// 	{
// 		if ((*file)->time > time)
// 		{
// 			new_t_file(file, name);
// 			return ;
// 		}
// 		file = &((*file)->next);
// 	}
// 	new_t_file(file, name);
// }

void	sort_files_by_name(t_file **file, t_file *new)
{
	while (*file)
	{
		if (ft_strcmp(new->name, (*file)->name) < 0)
		{
			new->next = *file;
			*file = new;
			return ;
		}
		file = &((*file)->next);
	}
	new->next = *file;
	*file = new;
}

void	sort_files_by_time(t_file **files, t_file *new)
{
	while (*files)
	{
		if ((*files)->time <= new->time)
		{
			if ((*files)->time == new->time)
			{
				while (*files && (*files)->time == new->time)
				{
					if (ft_strcmp(new->name, (*files)->name) < 0)
						break ;
					files = &((*files)->next);
				}
			}
			new->next = *files;
			*files = new;
			return ;
		}
		files = &((*files)->next);
	}
	new->next = *files;
	*files = new;
}

void	handle_folder_len(t_folder *folder, size_t len)
{
	if (folder->len_max < len)
		folder->len_max = len;
	folder->nb_files++;
}
