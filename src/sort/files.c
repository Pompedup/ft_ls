/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:15:45 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/03 00:32:07 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_file	**same_time(t_data *data, t_file **lst, t_file *new)
{
	int cmp;

	while (*lst && (*lst)->time == new->time)
	{
		cmp = ft_strcmp(new->name, (*lst)->name);
		if (data->options & OPTION_R ? cmp < 0 : cmp > 0)
			break ;
		lst = &((*lst)->next);
	}
	return (lst);
}

void		files_by_time(t_data *data, t_file **lst, t_file *new)
{
	while (*lst)
	{
		if ((data->options & OPTION_R) ? (*lst)->time >= new->time : (*lst)->time <= new->time)
		{
			if ((*lst)->time == new->time)
				lst = same_time(data, lst, new);
			break ;
		}
		lst = &((*lst)->next);
	}
	new->next = *lst;
	*lst = new;
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

void		files_by_name(t_data *data, t_file **lst, t_file *new)
{
	int cmp;

	while (*lst)
	{
		cmp = ft_strcmp(new->name, (*lst)->name);
		if ((data->options & OPTION_R) ? cmp > 0 : cmp < 0)
		{
			new->next = *lst;
			*lst = new;
			return ;
		}
		lst = &((*lst)->next);
	}
	new->next = *lst;
	*lst = new;
}

void		sort_files(t_data *data, t_file **files, t_file *new)
{
	if (data->options & OPTION_T)
		files_by_time(data, files, new);
	else
		files_by_name(data, files, new);
}
