/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:29:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/29 19:33:57 by abezanni         ###   ########.fr       */
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
# define EXEC_MASK 73


# define OPTIONS "Ralrt"
# define USAGE_PART1	"./ft_ls: illegal option -- %c\n"
# define USAGE_PART2	"usage: ./ft_ls [-%s] [file ...]\n"
# define USAGE 			USAGE_PART1 USAGE_PART2

# define UNEXIST_FILE	"./ft_ls %s: No sush file or directory\n"

typedef struct dirent	t_dirent;
typedef struct stat		t_stat;
typedef struct s_file	t_file;
typedef struct s_folder	t_folder;
typedef struct s_error	t_error;

struct s_error
{
	char			*name;
	t_error			*next;
};

struct s_file
{
	char			*name;
	t_bool			type;
	t_bool			exec;
	t_file		*next;
};

struct	s_folder
{
	DIR				*dir;
	t_dirent		*file;
	t_file			*files;
	size_t			len_max;
	char			*name;
	size_t			nb_files;
	t_folder	*next;
};

typedef struct	s_data
{
	t_folder		*folders;
	t_folder		*files;
	t_error			*errors;
	int				options;
}				t_data;
//boom
t_bool	is_exec(char *link, char *name, t_bool *folder, t_bool *exec);
void	handle_folder(t_folder *folder, size_t len);

//handle open_dirs
void	open_dirs(t_data *data, int ac, char **av);

//handle options
int		options(char *str, int options);

//handle file
void	sort_files(t_file **file, char *name, int type, t_bool exec);


//struct error
void	del_t_error(t_error **current);
void	del_t_errors(t_error **current);
void	new_t_error(t_error **current, char *name);

//struct file
void	del_t_file(t_file **current);
void	del_t_files(t_file **current);
void	new_t_file(t_file **current, char *name, t_bool type, t_bool exec);


//struct folder
void	del_t_folder(t_folder **current);
void	del_t_folders(t_folder **current);
void	new_t_folder(t_folder **current, char *name);
#endif
