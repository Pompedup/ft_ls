/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:32:08 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/04 17:11:34 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_file(t_file **current)
{
	t_file *to_free;

	to_free = *current;
	free((*current)->name);
	free((*current)->link);
	free((*current)->rights);
	free((*current)->uid);
	free((*current)->gid);
	free((*current)->sym_link);
	*current = (*current)->next;
	free(to_free);
}

void	del_t_files(t_file **current)
{
	while (*current)
		del_t_file(current);
}

void	new_t_file(t_file **current, char *link)
{
	if (!(*current = ft_memalloc(sizeof(t_file))))
		return ;
	(*current)->link = link;
	(*current)->next = NULL;
}
