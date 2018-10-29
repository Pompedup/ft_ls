/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 18:45:58 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_folder(t_folder **current)
{
	t_folder *to_free;

	to_free = *current;
	*current = (*current)->next;
	free(to_free);
}

void	del_t_folders(t_folder **current)
{
	while (*current)
		del_t_folder(current);
}

void	new_t_folder(t_folder **current, char *name)
{
	if (!(*current = ft_memalloc(sizeof(t_folder))))
		return ;
	if (name)
		(*current)->name = ft_strdup(name);
}
