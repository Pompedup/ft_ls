/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 16:40:38 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/01 18:18:49 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	display_name(t_bool folder, t_bool exec, size_t len, char *name)
{
	if (folder)
		ft_printf(DIR_COLOR, len, name);
	else if (exec)
		ft_printf(EXEC_COLOR, len, name);
	else
		ft_printf("%-*s ", len, name);
}

void	display(t_folder *folder, t_bool write)
{
    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	while (folder)
	{
		if (write)
			ft_printf("%s:\n", folder->name);
		else
			write = TRUE;
		if (folder->files)
		{
			if (w.ws_col < folder->nb_files * (folder->len_max + 1))
				adjust(folder, w.ws_col);
			else
				right_size(folder, folder->files);
		}
		if (folder->subfolders)
		{
			ft_printf("\n");
			display(folder->subfolders, TRUE);
		}
		if ((folder = folder->next))
			ft_printf("\n");
	}
}
