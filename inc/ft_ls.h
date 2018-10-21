/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:29:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 20:25:23 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libft/inc/libft.h"

# include <dirent.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <time.h>

# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>


# include <sys/ioctl.h>//bonus affichage

typedef struct dirent	t_dirent;
typedef struct s_data_file	t_data_file;
typedef struct s_data_folder t_data_folder;

struct s_data_file
{
	char			*name;
	int				type;
	t_data_file		*next;
};

struct	s_data_folder
{
	t_data_file		*files;
	size_t			len_max;
	size_t			nb_files;
	t_data_folder	*next;
};


void	del_t_data_file(t_data_file **current);
void	del_t_data_files(t_data_file **current);
void	new_t_data_file(t_data_file **current, char *name, int type);

void	del_t_data_folder(t_data_folder **current);
void	del_t_data_folders(t_data_folder **current);
void	new_t_data_folder(t_data_folder **current);
#endif
