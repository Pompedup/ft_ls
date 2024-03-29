/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   right_size.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/04 12:55:32 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/01 11:46:54 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	right_size(t_folder *folder, t_file *current)
{
	while (current)
	{
		display_name(current->type, TRUE/*exec*/, folder->len_max, current->name);
		current = current->next;
	}
	ft_printf("\n");
}
