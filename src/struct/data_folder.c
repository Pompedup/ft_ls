/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_folder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 18:36:17 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 18:54:13 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	del_t_data_folder(t_data_folder **current)
{
	t_data_folder *to_free;

	to_free = *current;
	*current = (*current)->next;
	free(to_free);
}

void	del_t_data_folders(t_data_folder **current)
{
	while (*current)
		del_t_data_folder(current);
}

void	new_t_data_folder(t_data_folder **current)
{
	if (!(*current = ft_memalloc(sizeof(t_data_folder))))
		return ;
}
