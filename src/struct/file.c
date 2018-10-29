/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:32:08 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 19:30:33 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_file(t_file **current)
{
	t_file *to_free;

	to_free = *current;
	free((*current)->name);
	*current = (*current)->next;
	free(to_free);
}

void	del_t_files(t_file **current)
{
	while (*current)
		del_t_file(current);
}

void	new_t_file(t_file **current, char *name, t_bool type, t_bool exec)
{
	t_file *next;

	next = *current;
	if (!(*current = ft_memalloc(sizeof(t_file))))
		return ;
	(*current)->name = ft_strdup(name);
	(*current)->type = type;
	(*current)->exec = exec;
	(*current)->next = next;
}
