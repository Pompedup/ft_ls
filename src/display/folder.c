/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:47:53 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/05 17:54:29 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>
#include <sys/acl.h>

char	*get_color(char type, char *rights, int options)
{
	if (options & OPTION_Z)
		return (NO_COLOR);
	if (type == 'd')
		return (DIR_COLOR);
	else if (type == 'l')
		return (LNK_COLOR);
	else if (type == 's')
		return (SOCK_COLOR);
	else if (type == 'p')
		return (IFO_COLOR);
	else if (type == 'c')
		return (CHR_COLOR);
	else if (rights[2] == 'x' || rights[5] == 'x' || rights[8] == 'x')
		return (EXEC_COLOR);
	else if (type == 'b')
		return (BLK_COLOR);
	return (NO_COLOR);
}

char	*too_old(time_t mytime)
{
	time_t	actual;
	char	*in_letter;

	in_letter = ctime(&mytime);
	time(&actual);
	if (mytime < actual - DIFF_TIME || mytime > actual)
		ft_strcpy(in_letter + 11, in_letter + 19);
	return (in_letter);
}

char	get_attribute(char *path, char type)
{
	if (type == 'l')
		return (' ');
	if (listxattr(path, NULL, 0, 0) > 0)
		return ('@');
	if (acl_get_file(path, ACL_TYPE_EXTENDED))
		return ('+');
	return (' ');
}

void	display_l(t_folder *folder, t_file *file, char *color, size_t len_time)
{
	char buf[100000];
	if (!(file->type == 'l'))
		ft_printf(BASIC_L, file->type,\
			file->rights, get_attribute(file->link, file->type), folder->link_len + 1, file->nb_links\
			, folder->uid_len + 1, file->uid, folder->gid_len + 1, file->gid\
			, folder->size_len + 1, file->size, len_time, too_old(file->time) + 4\
			, color, file->name, *color ? END_COLOR : NO_COLOR);
	else
	{
		ft_printf("%zu\n", readlink(file->link, buf, 100000));
		ft_printf(SYM_LINK_L, file->type,\
			file->rights, get_attribute(file->link, file->type), folder->link_len + 1, file->nb_links\
			, folder->uid_len + 1, file->uid, folder->gid_len + 1, file->gid\
			, folder->size_len + 1, file->size, len_time, too_old(file->time) + 4\
			, color, file->name, *color ? END_COLOR : NO_COLOR, buf);
	}
}

void	display_line(t_data *data, int options, t_folder *folder, size_t len_time)
{
	t_file	*file;
	char	*color;
	int errno;

	errno = 0;
	file = folder->files;
	if (!file)
		return ;
	if (folder->dir)
		ft_printf("total %zu\n", folder->blocks);
	while (file)
	{
		color = get_color(file->type, file->rights, options);
		display_l(folder, file, color, len_time);
		if ((ft_strcmp(".", file->name) && ft_strcmp("..", file->name)))
			if (options & OPTION_BIGR && file->type == 'd')
				if (is_dir(data, &folder->subfolders, file->link, TRUE) == 0)
					ft_fprintf(2, "ls: %s: %s\n", file->name, strerror(errno));
		file = file->next;
	}
}

void	display_folder(t_data *data, t_folder *folder)
{
	if (!folder)
		return ;
	if (data->already_print)
		ft_printf("\n%s:\n", folder->name);
	else if (data->print_name && folder->dir)
		ft_printf("%s\n", folder->name);
	if (!folder->dir && !folder->files)
		return ;
	if (data->options & OPTION_L)
		display_line(data, data->options, folder, data->len_time);
	else
		display_column(data->ws_col, data->options, folder);
	data->already_print = TRUE;
}
