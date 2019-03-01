/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 17:47:53 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/01 18:36:49 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <stdio.h>

char	*get_color(char *buf, char type, char *rights)
{
	if (type == 'd')
		return (DIR_COLOR);
	else if (type == 'l')
		return (LNK_COLOR);
	else if (type == 's')
		return (SOCK_COLOR);
	else if (type == 'p')
		return (IFO_COLOR);
	else if (rights[2] == 'x' || rights[5] == 'x' || rights[8] == 'x')
		return (EXEC_COLOR);
	else if (type == 'b')
		return (BLK_COLOR);
	else if (type == 'c')
		return (CHR_COLOR);
	return (buf);
}

void	display_l(t_folder *folder)
{
	t_file	*file;
	char	buf[1];

	file = folder->files;
	*buf = '\0';
	while (file)
	{
		ft_printf("%c%s%*hu%*s%*s%*lld%*.*s \033[%sm%s\033[0m\n", file->type,\
			file->rights, folder->link_len + 2, file->nb_links, folder->uid_len + 1,\
			file->uid, folder->gid_len + 1, file->gid, 8,\
			file->size, 13, 12, file->time + 4, get_color(buf, file->type,\
			file->rights), file->name);
		file = file->next;
	}
}

void	display_folder(t_data *data, t_folder *folder)
{
	if (data->options & OPTION_L)
		display_l(folder);
}
