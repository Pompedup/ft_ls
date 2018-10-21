/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:32:08 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 20:17:15 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_data_file(t_data_file **current)
{
	t_data_file *to_free;

	to_free = *current;
	free((*current)->name);
	*current = (*current)->next;
	free(to_free);
}

void	del_t_data_files(t_data_file **current)
{
	while (*current)
		del_t_data_file(current);
}

void	new_t_data_file(t_data_file **current, char *name, int type)
{
	t_data_file *next;

	next = *current;
	if (!(*current = ft_memalloc(sizeof(t_data_file))))
		return ;
	(*current)->name = ft_strdup(name);
	(*current)->type = type;
	(*current)->next = next;
}
