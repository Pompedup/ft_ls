/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   folder.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:26:47 by abezanni          #+#    #+#             */
/*   Updated: 2019/02/27 17:29:54 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static t_bool	get_data(t_data *data, char *link)
{
	t_stat	buf;

	if (stat(link, &buf) == -1)
		return (FALSE);
		//new t_file
	if (data->options & (OPTION_L | OPTION_T))
		file->time = ft_strdup(ctime(buf.st_mtimespec.tv_sec));
	if (data->options & (OPTION_L))
	{
		file->type = ;		//type
		file->rights = ;	//droits
		file->?? = ;		//int
		file->owner = ;		//proprietaire
		file->?? = ;		//2017_paris
		file-> ?? = ;		//gros int
		file->name = ;		//name _ lolilol
	}
}

static t_bool	handle_folder(t_data *data, t_container *folder)
{

//	if (data->options & OPTION_BIGR)
		//do recursion
	get_data(data, );
}

t_bool	folders(t_data *data, t_container **folders)
{
	while (*folders)
	{
		if (!(handle_folder(data, *folders)))
			return (FALSE);
		del_t_container(folders);
	}
	return (TRUE);
}
