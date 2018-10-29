/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 17:27:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 17:59:50 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_error(t_error **current)
{
	t_error *to_free;

	to_free = *current;
	*current = (*current)->next;
	ft_printf(UNEXIST_FILE, to_free->name);
	free(to_free);
}

void	del_t_errors(t_error **current)
{
	while (*current)
		del_t_error(current);
}

void	new_t_error(t_error **current, char *name)
{
	t_error *next;

	while (*current && ft_strcmp((*current)->name, name) < 0)
		current = &((*current)->next);
	next = *current;
	if (!(*current = ft_memalloc(sizeof(t_error))))
		return ;
	(*current)->name = name;
	(*current)->next = next;
}
