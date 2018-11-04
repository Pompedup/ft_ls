/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:29:59 by abezanni          #+#    #+#             */
/*   Updated: 2018/11/04 18:17:34 by abezanni         ###   ########.fr       */
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
# define OPTION_BIGR	1 << 0
# define OPTION_A		1 << 1
# define OPTION_L		1 << 2
# define OPTION_R		1 << 3
# define OPTION_T		1 << 4
# define USAGE_PART1	"./ft_ls: illegal option -- %c\n"
# define USAGE_PART2	"usage: ./ft_ls [-%s] [file ...]\n"
# define USAGE 			USAGE_PART1 USAGE_PART2
# define FOLDER			"\033[1;36m%-*s \033[0m"
# define EXEC			"\033[0;31m%-*s \033[0m"
# define END			""

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
	time_t			time;
	t_file			*next;
	off_t			size;
};

struct	s_folder
{
	DIR				*dir;
	t_dirent		*file;
	t_file			*files;
	t_folder		*subfolders;
	size_t			len_max;
	char			*name;
	size_t			nb_files;
	time_t			time;
	off_t			size;
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
void	handle_folder_len(t_folder *folder, size_t len);
t_bool	get_stats(char *link, char *name, t_stat *buf);

//display adjust
void	adjust(t_folder *folder, size_t len_col);

//display right_size
void	right_size(t_folder *folder, t_file *current);

//display display
void	display_name(t_bool folder, t_bool exec, size_t len, char *name);
void	display(t_folder *folder, t_bool write);

//handle file
void	sort_files_by_name(t_file **file, t_file *new);
void	sort_files_by_time(t_file **file, t_file *new);

//handle folder
void	sort_folders_by_time(t_folder **folders, t_folder *new);
void	sort_folders_by_name(t_folder **folders, t_folder *new);

//handle open_dirs
void	open_dirs(t_data *data, int ac, char **av);

//handle options
int		options(char *str, int options);

//handle file
void	sort_files_by_name(t_file **file, t_file *new);

//handle folder
void	handle_folders(t_data *data, t_folder *folders);

//options reverse
void	reverse(t_folder **add_first, t_folder *folder);

//step
void	init(t_data *data, int *i);

//struct error
void	del_t_error(t_error **current);
void	del_t_errors(t_error **current);
void	new_t_error(t_error **current, char *name);

//struct file
void	del_t_file(t_file **current);
void	del_t_files(t_file **current);
void	new_t_file(t_file **current, char *name);


//struct folder
void	del_t_folder(t_folder **current);
void	del_t_folders(t_folder **current);
void	new_t_folder(t_folder **current, char *name, DIR *dir);
#endif
