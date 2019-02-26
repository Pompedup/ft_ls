/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:12:53 by abezanni          #+#    #+#             */
/*   Updated: 2019/02/26 19:47:15 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_container(t_container **current)
{
	t_container *to_free;

	to_free = *current;
	if ((*current)->dir)
		closedir((*current)->dir);
	free((*current)->name);
	*current = (*current)->next;
	free(to_free);
}

void	del_t_containers(t_container **current)
{
	while (*current)
		del_t_container(current);
}

void	new_t_container(t_container **current, char *name, DIR *dir)
{
	if (!(*current = ft_memalloc(sizeof(t_container))))
		return ;
	(*current)->dir = dir;
	(*current)->name = name;
	(*current)->next = NULL;
}
