/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 17:38:31 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_folder(t_folder *folder)
{
	t_file *file;

	file = folder->files;
}

void	print_folders(t_folder *current)
{
	while (current)
	{
		display(current, TRUE);
		if (current->subfolders)
			print_folders(current->subfolders);
		current = current->next;
	}
}

void	del_t_folder(t_folder **current)
{
	t_folder *to_free;

	to_free = *current;
	*current = (*current)->next;
	free(to_free->name);
	del_t_files(&to_free->files);
	del_t_folders(&to_free->subfolders);
	free(to_free);
}

void	del_t_folders(t_folder **current)
{
	while (*current)
		del_t_folder(current);
}

void	new_t_folder(t_folder **current, char *name, DIR *dir)
{
	t_folder *next;

	next = *current;
	if (!(*current = ft_memalloc(sizeof(t_folder))))
		return ;
	(*current)->name = name;
	(*current)->dir = dir;
	if (!dir)
	if (!((*current)->dir = opendir(name)))
	{
		//error message
	}
	(*current)->next = next;
}
