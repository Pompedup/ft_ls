/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 17:24:11 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/03 16:51:22 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	adjust_files(t_file **files, size_t nb_files, size_t per_line)
{
	size_t	nb_lines;
// 	size_t	lines_full;

	(void)files;
	if (!per_line)
	{
		per_line++;
		// lenght_max = 0; // a ajouter bolosse !!!
	}
	nb_lines = nb_files / per_line + (nb_files % per_line > 0);
	per_line = nb_files / nb_lines + (nb_files % nb_lines > 0);
// 	sort_by_line(&folder->files, nb_lines - 1);
// 	lines_full = nb_line_file(nb_lines, folder->nb_files) - 1;
// 	repeat(folder, lines_full, tmp);
}

void	display_files(t_folder **files, size_t max_lenght, size_t nb_files)
{
    struct winsize	w;
	t_file			*file;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	file = (*files)->files;
	if (w.ws_col < nb_files * (max_lenght + 1))
		adjust_files(&(*files)->files, nb_files, w.ws_col / (max_lenght + 1));
	while (file)
	{
		ft_printf("%s\n", file->name);
		file = file->next;
	}
	ft_printf("%zu - %zu\n", max_lenght, nb_files);
}
