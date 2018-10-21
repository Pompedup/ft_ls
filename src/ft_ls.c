/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abezanni <abezanni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/21 17:43:16 by abezanni          #+#    #+#             */
/*   Updated: 2018/10/21 20:43:24 by abezanni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	get_infos(t_data_folder *folder, t_data_file **file, t_dirent *dirent)
{
	if (folder->len_max < dirent->d_namlen)
		folder->len_max = dirent->d_namlen;
	folder->nb_files++;
	while (*file)
	{
		if (ft_strcmp(dirent->d_name, (*file)->name) < 0)
		{
			new_t_data_file(file, dirent->d_name, dirent->d_type);
			return ;
		}
		file = &((*file)->next);
	}
	new_t_data_file(file, dirent->d_name, dirent->d_type);
}

void	one_on_x(t_data_folder *folder, size_t len_col)
{
	size_t	word;
	size_t	i;

	i = 0;
	while ((i + 1) * (folder->len_max + 1) < len_col)
		i++;
	word = folder->nb_files / i + (folder->nb_files % i > 0);
	ft_printf("%d - %d - %d - %d", word, i , len_col, folder->len_max);
}

void	aff(t_data_folder *folder)
{
    struct winsize w;
	t_data_file *current;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	if (w.ws_col < folder->nb_files * (folder->len_max + 1))
		one_on_x(folder, w.ws_col);
	else
	{
		current = folder->files;
		while (current)
		{
			if (current->type == 4)
				ft_printf("\033[1;36m");
			ft_printf("%-*s ", folder->len_max, current->name, current->type);
			if (current->type == 4)
				ft_printf("\033[0m");
			current = current->next;
		}
	}
	ft_printf("\n");
}

int		main(int ac, char **av)
{
	(void)ac;
	(void)av;
	DIR *testdir;
	t_dirent *testdirent;
	t_data_folder *data;


	testdir = opendir(".");
	new_t_data_folder(&data);
	while ((testdirent = readdir(testdir)))
	{
		if (*testdirent->d_name != '.')
			get_infos(data, &data->files, testdirent);
	}
	aff(data);
	// ft_printf("%s ", testdirent->d_name);
	closedir(testdir);
	return (0);
}

// #include <sys/ioctl.h>
    // struct winsize w;
    // ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    // printf ("lines %d\n", w.ws_row);
    // printf ("columns %d\n", w.ws_col);


// ◦ write
// Ecrire sur le terminal


// ◦ DIR *opendir(const char *filename)
// Ouvre le dossier filename et retourne un poiteur qui identifie le directory stream
// Retourne NULL si filename est innacessible (errno explique l'erreur)

// ◦ struct dirent *readdir(DIR *)
// struct dirent { /* when _DARWIN_FEATURE_64_BIT_INODE is NOT defined */
//              ino_t      d_ino;                /* file number of entry */
//              __uint16_t d_reclen;             /* length of this record */
//              __uint8_t  d_type;               /* file type, see below */
//              __uint8_t  d_namlen;             /* length of string in d_name */
//              char    d_name[255 + 1];   /* name must be no longer than this */
//      };
// Retourne un pointeur contenant les infos du prochain fichier/dossier
// Retourne NULL a la fin de la lecture ou si une erreur se produit

// ◦ int closedir(DIR *)
// Ferme un fichier ouvert avec opendir et free la structure
// Retourne 0 si tout est bon
//  -1 en cas d'erreur ->errno
// ◦ int stat(const char *restrict path, struct stat *restrict buf)
// Recupere les informations du fichier pointe par path

// ◦ int lstat(const char *restrict path, struct stat *restrict buf)
// Comme stat mais avec un lien symbolic,
// The lstat() function is like stat() except in the case where the named file is a symbolic link; lstat() returns information about the link, while stat() returns information about the file the link
    //  references.  For symbolic links, the st_mode member contains meaningful information when used with the file type macros, and the st_size member contains the length of the pathname contained in the
    //  symbolic link. File mode bits and the contents of the remaining members of the stat structure are unspecified. The value returned in the st_size member is the length of the contents of the sym-
    //  bolic link, and does not count any trailing null.


// ◦ struct passwd *getpwuid(uid_t uid)
//
// struct passwd {
//                    char    *pw_name;       /* user name */
//                    char    *pw_passwd;     /* encrypted password */
//                    uid_t   pw_uid;         /* user uid */
//                    gid_t   pw_gid;         /* user gid */
//                    time_t  pw_change;      /* password change time */
//                    char    *pw_class;      /* user access class */
//                    char    *pw_gecos;      /* Honeywell login info */
//                    char    *pw_dir;        /* home directory */
//                    char    *pw_shell;      /* default shell */
//                    time_t  pw_expire;      /* account expiration */
//                    int     pw_fields;      /* internal: fields filled in */
// };
// ◦ getgrgid
// These functions obtain information from opendirectoryd(8), including records in /etc/group which is described in group(5).  Each line of the database is defined by the structure group found in the
//      include file <grp.h>:

//            struct group {
//                    char    *gr_name;       /* group name */
//                    char    *gr_passwd;     /* group password */
//                    gid_t   gr_gid;         /* group id */
//                    char    **gr_mem;       /* group members */
//            };
// ◦ ssize_t listxattr(const char *path, char *namebuf, size_t size, int options);
// ◦ ssize_t getxattr(const char *path, const char *name, void *value, size_t size, u_int32_t position, int options);
// ◦ time_t time(time_t *tloc)
// ◦ char * ctime(const time_t *clock)

// ◦ ssize_t readlink(const char *restrict path, char *restrict buf, size_t bufsize)


// ◦ void perror(const char *s)
// ◦ char * strerror(int errnum)

// ◦ malloc
// ◦ free
// ◦ exit


//ls -lRart (-l droits ?)
