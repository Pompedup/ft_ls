/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:29:59 by abezanni          #+#    #+#             */
/*   Updated: 2019/03/02 10:41:35 by abezanni         ###   ########.fr       */
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
# include <grp.h>

# include <sys/ioctl.h>//bonus affichage
# define EXEC_MASK 73

# define OPTIONS		"Ralrt"
# define OPTION_BIGR	1 << 0
# define OPTION_A		1 << 1
# define OPTION_L		1 << 2
# define OPTION_R		1 << 3
# define OPTION_T		1 << 4
# define USAGE_PART1	"./ft_ls: illegal option -- %c\n"
# define USAGE_PART2	"usage: ./ft_ls [-%s] [file ...]\n"
# define USAGE 			USAGE_PART1 USAGE_PART2
# define DIR_COLOR		"1;36"
# define LNK_COLOR		"35"
# define SOCK_COLOR		"32"
# define IFO_COLOR		"33"
# define EXEC_COLOR		"31"
# define BLK_COLOR		"33;40"
# define CHR_COLOR		"34;43"
# define END_COLOR		""

# define UNEXIST_FILE	"./ft_ls %s: No sush file or directory\n"

typedef struct dirent		t_dirent;
typedef struct stat			t_stat;
typedef struct s_file		t_file;
typedef struct s_folder		t_folder;
typedef struct s_container	t_container;
typedef struct s_error		t_error;

struct	s_error
{
	char			*name;
	t_error			*next;
};

struct	s_file
{
	char			*link;
	char			*name;
	time_t			time;
	char			type;
	char			*rights;
	nlink_t			nb_links;
	char			*uid;
	char			*gid;
	off_t			size;
	char			*sym_link;
	t_file			*next;
};

struct	s_folder
{
	char			*name;
	DIR				*dir;
	t_file			*files;
	t_folder		*subfolders;
	time_t			time;
	size_t			len_max;
	size_t			nb_files;
	size_t			uid_len;
	size_t			gid_len;
	size_t			link_len;
	t_folder		*next;
};

struct	s_container
{
	DIR				*dir;
	char			*name;
	time_t			time;
	t_container		*next;
};

typedef struct	s_data
{
	t_container		*container_dir;
	t_container		*container_files;
	size_t			nb_files;
	size_t			max_lenght;
	t_folder		*folders;//
	t_folder		*files;//
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
int		options(char *str);

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

void	del_t_container(t_container **current);
void	del_t_containers(t_container **current);
void	new_t_container(t_container **current, char *name, DIR *dir);


// t_container	**same_time(t_data *data, t_container **lst, t_container *new);
void		container_by_time(t_data *data, t_container **lst, t_container *new);
void		container_by_name(t_data *data, t_container **lst, t_container *new);

void	test_link(t_data *data, char *link);
void	args(t_data *data, int ac, char **av);

void	display_files(t_container **files, size_t max_lenght, size_t nb_files);

t_bool	get_folders(t_data *data, t_container **folders);

void	display_folder(t_data *data, t_folder *folder);

void		sort_files(t_data *data, t_file **files, t_file *new);

#endif
