/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:36:38 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 21:15:59 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
********************************************************************************
**	Function: sort_files_by_name
**	----------------
**		Place a file in the list at the right place by alphabetic order
**
**		file: the list of files
**		new: the new file
**	****
**
**   returns: nothing
********************************************************************************
*/

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

/*
********************************************************************************
**	Function: sort_files_by_time
**	----------------
**		Place a file in the list at the right place by last time of modification
**
**		file: the list of files
**		new: the new file
**	****
**
**   returns: nothing
********************************************************************************
*/

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

/*
********************************************************************************
**	Function: handle_folder_len
**	----------------
**		Verify if the len is greater than the one register before and modify
**			it if it's necessary
**
**		folder: the folder we actualy use
**		len: the len to compare
**
**   returns: nothing
********************************************************************************
*/

void	handle_folder_len(t_folder *folder, size_t len)
{
	if (folder->len_max < len)
		folder->len_max = len;
	folder->nb_files++;
}
