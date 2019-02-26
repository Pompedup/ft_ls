/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:24:01 by abezanni          #+#    #+#             */
/*   Updated: 2019/02/26 16:50:53 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_container	**same_time(t_data *data, t_container **lst, t_container *new)
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

void		container_by_time(t_data *data, t_container **lst, t_container *new)
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

void		container_by_name(t_data *data, t_container **lst, t_container *new)
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
