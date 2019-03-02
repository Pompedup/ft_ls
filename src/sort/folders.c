/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 10:42:00 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/02 10:43:02 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_folder	**same_time(t_data *data, t_folder **lst, t_folder *new)
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

void		folders_by_time(t_data *data, t_folder **lst, t_folder *new)
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

void		folders_by_name(t_data *data, t_folder **lst, t_folder *new)
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

void		sort_folders(t_data *data, t_folder **folders, t_folder *new)
{
	if (data->options & OPTION_T)
		folders_by_time(data, folders, new);
	else
		folders_by_name(data, folders, new);
}
