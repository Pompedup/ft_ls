/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 12:43:36 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/03 17:35:23 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static char		*get_gid(t_stat *buf, t_folder *folder)
{
	struct group	*gid;
	size_t			len;

	if (!(gid = getgrgid(buf->st_gid)))
		return (NULL);
	if (folder->gid_len < (len = ft_strlen(gid->gr_name)))
		folder->gid_len = len;
	return (ft_strdup(gid->gr_name));
}

static char		*get_sym_link(char *link)
{
	char	buf[256];
	int		ret;

	if ((ret = readlink(link, buf, 255)) == -1)
		return (NULL);
	buf[ret] = '\0';
	return (ft_strdup(buf));
}

t_bool	get_option_l(t_stat	*buf, t_file *new, t_folder *folder)
{
	if (!(new->gid = get_gid(buf, folder)))
		return (FALSE);
	if (new->type == 'l')
		if (!(new->sym_link = get_sym_link(new->link)))
			return (FALSE);
	return (TRUE);
}
