/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/29 16:36:38 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 19:10:43 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	sort_files(t_file **file, char *name, int type, t_bool exec)
{
	while (*file)
	{
		if (ft_strcmp(name, (*file)->name) < 0)
		{
			new_t_file(file, name, type, exec);
			return ;
		}
		file = &((*file)->next);
	}
	new_t_file(file, name, type, exec);
}

void	handle_folder(t_folder *folder, size_t len)
{
	if (folder->len_max < len)
		folder->len_max = len;
	folder->nb_files++;
}
