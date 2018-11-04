/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 13:36:08 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 15:55:13 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
********************************************************************************
**	Function: push_top
**	----------------
**		Put new_first at the begin of the list
**
**		add_first: the adress of the first elem of the list
**		prev_first: the first elem at the beggining
**		new_first: an elem to put at the begin of the chained list
**
**   returns: nothing
********************************************************************************
*/

void	push_top(t_folder **add_first, t_folder *prev_first, t_folder *new_first)
{
	prev_first->next = new_first->next;
	new_first->next = *add_first;
	*add_first = new_first;
}

/*
********************************************************************************
**	Function: reverse_files
**	----------------
**		Put next at the begin of the list until the list is reverse
**
**		add_first: the adress of the first elem of the list
**		file: the first elem at the beggining
**	****
**		next: an elem to put at the begin of the chained list
**
**   returns: nothing
********************************************************************************
*/

void	reverse_files(t_file **add_first, t_file *file)
{
	t_file *next;

	while (file->next)
	{
		next = file->next;
		file->next = next->next;
		next->next = *add_first;
		*add_first = next;
	}
}

/*
********************************************************************************
**	Function: reverse
**	----------------
**		Call push_top for all the folder of the list, call herself for
**			all the subfolders list contained by folders and call reverse_files
**			for all the files list contained by folders
**
**		add_first: the adress of the first elem of the list
**		folder: the first elem at the beggining
**	****
**		next: an elem to put at the begin of the chained list
**
**   returns: nothing
********************************************************************************
*/

void	reverse(t_folder **add_first, t_folder *folder)
{
	t_folder *next;

	while (folder->next)
	{
		next = folder->next;
		if (next->files)
			reverse_files(&next->files, next->files);
		push_top(add_first, folder, next);
		if (next->subfolders)
			reverse(&next->subfolders, next->subfolders);
	}
	if (folder->files)
		reverse_files(&folder->files, folder->files);
	if (folder->subfolders)
		reverse(&folder->subfolders, folder->subfolders);
}
